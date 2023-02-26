import sys
import regex
import json

re = regex

files = {}

for filename in sys.argv:
    with open(filename, 'r') as file:
        files[filename] = file.read()

exprs = {}
exprs["reference"] = "\((\w+)\s*,\s*(\w+),\s(\w+)\)"
exprs["type_reference"] = "TYPE\s*{reference}".format_map(exprs)

exprs["type_declaration"] = "DECLARE_TYPE\s*{reference}\s*;".format_map(exprs)
exprs["type_property_getter"] = "DECLARE_PROPERTY_TYPE_GETTER\s*\(\s*{type_reference}\s*,\s*(\w+)\s*,\s*{type_reference}\s*\)\s*;".format_map(exprs)
exprs["type_property_setter"] = "DECLARE_PROPERTY_TYPE_SETTER\s*\(\s*{type_reference}\s*,\s*(\w+)\s*,\s*{type_reference}\s*\)\s*;".format_map(exprs)

exprs["parameter"] = "PARAMETER\s*\(\s*(\w+)\s*,\s*{type_reference}\s*\)".format_map(exprs)
exprs["function_reference"] = "FUNCTION\s*{reference}".format_map(exprs)
exprs["result"] = "RESULT\s*\(?\s*{type_reference}\s*\)".format_map(exprs)
exprs["function_declaration"] = "DECLARE_FUNCTION\s*\(\s*{function_reference}\s*(?:\s*,\s*{parameter})*(?:\s*,\s*{result})?\s*\)\s*;".format_map(exprs)
exprs["type_function_declaration"] = "DECLARE_TYPE_FUNCTION\s*\(\s*{type_reference}\s*,\s*(\w+)\s*(?:\s*,\s*{parameter})*(?:\s*,\s*{result})?\s*\)\s*;".format_map(exprs)

modules = {}

def create_type_decl(name):
    return {
        "Struct": {
            "name": name,
            "properties": [],
            "functions": []
        }
    }

def create_function_decl(name):
    return {
        "Function": {
            "name": name,
            "inputs": [],
        }
    }

def create_param(name, owner, project, t):
    return {
        "name": name,
        "type": "{}/{}/{}".format(owner, project, t),
    }

def create_property(name, owner, project, t):
    return {
        "name": name,
        "type": "{}/{}/{}".format(owner, project, t),
    }

def get_type(module, name):
    for d in modules[module]["declarations"]:
        if "Struct" in d and d["Struct"]["name"] == name:
            return d["Struct"]
    return None

def get_property(type_, name):
    for p in type_["properties"]:
        if p["name"] == name:
            return p
    return None


for f in files:
    content = files[f]

    for m in re.finditer(exprs["type_declaration"], content):
        module = "{}/{}".format(m[1], m[2])
        if not module in modules:
            modules[module] = {
                "module": module,
                "declarations": []
            }
        modules[module]["declarations"].append(create_type_decl(m[3]))

    for m in re.finditer(exprs["type_property_getter"], content):
        type_ = get_type("{}/{}".format(m[1], m[2]), m[3])
        prop = get_property(type_, m[4])
        if prop == None:
            prop = create_property(m[4], m[5], m[6], m[7])
            prop["get"] = True
            type_["properties"].append(prop)
        else:
            prop["get"] = True

    for m in re.finditer(exprs["type_property_setter"], content):
        type_ = get_type("{}/{}".format(m[1], m[2]), m[3])
        prop = get_property(type_, m[4])
        if prop == None:
            prop = create_property(m[4], m[5], m[6], m[7])
            prop["set"] = True
            type_["properties"].append(prop)
        else:
            prop["set"] = True

    for m in re.finditer(exprs["type_function_declaration"], content):
        t = get_type("{}/{}".format(m[1], m[2]), m[3])
        f = create_function_decl(m[4])["Function"]
        for i in range(0, len(m.captures(5))):
            f["inputs"].append(create_param(m.captures(5)[i], m.captures(6)[i], m.captures(7)[i], m.captures(8)[i]))
        if m[9] != None:
            f["output"] = "{}/{}/{}".format(m[9], m[10], m[11])
        t["functions"].append(f)
    
    for m in re.finditer(exprs["function_declaration"], content):
        module = "{}/{}".format(m[1], m[2])
        if not module in modules:
            modules[module] = {
                "module": module,
                "declarations": []
            }
        f = create_function_decl(m[3])
        for i in range(0, len(m.captures(4))):
            f["Function"]["inputs"].append(create_param(m.captures(4)[i], m.captures(5)[i], m.captures(6)[i], m.captures(7)[i]))
        if m[8] != None:
            f["Function"]["output"] = "{}/{}/{}".format(m[8], m[9], m[10])

        modules[module]["declarations"].append(f)

for m in modules:
    with open("{}.json".format(m.replace("/", "--")), "w") as write:
        json.dump(modules[m], write)
