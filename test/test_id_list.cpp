#include "catch2/catch_test_macros.hpp"
#include "id_list.hpp"

TEST_CASE("IdList", "[ovis][runtime][idlist]") {
    SECTION("Empty list") {
        IdList l;
        REQUIRE(l.count() == 0);

        for (auto id : l) {
            REQUIRE(false);
        }
    }

    SECTION("Behaves correctly") {
        IdList l;
        REQUIRE(l.count() == 0);

        const auto inserted_id = l.emplace();
        REQUIRE(IdList::Id::index(inserted_id) == 0);
        REQUIRE(IdList::Id::version(inserted_id) == 0);

        REQUIRE(l.count() == 1);

        auto count = 0;
        for (const auto id : l) {
            REQUIRE(id == inserted_id);
            ++count;
        }
        REQUIRE(count == 1);

        l.remove(inserted_id);
        for (auto id : l) {
            REQUIRE(false);
        }
        REQUIRE(l.count() == 0);
        REQUIRE(!l.contains(inserted_id));

        const auto next_inserted_id = l.emplace();
        REQUIRE(next_inserted_id != inserted_id);
        REQUIRE(l.count() == 1);

        count = 0;
        for (const auto id : l) {
            REQUIRE(id == next_inserted_id);
            ++count;
        }
        REQUIRE(count == 1);
    }
}

