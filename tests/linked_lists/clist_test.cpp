#include <gtest/gtest.h>
#include <string>

extern "C" {
#include "../../src/linked_lists/clist.h"
#include "../../src/linked_lists/types.h"
}

namespace {

    class CircularLinkedListTest : public ::testing::Test {
    public:
        ll_clist_t l;

    protected:
        CircularLinkedListTest() {
            ll_clist_alloc_cell(&l);
            ll_clist_init(&l);
        }

        virtual ~CircularLinkedListTest() {
        }
    };

    TEST_F(CircularLinkedListTest, InsertingInEmptyList) {
        ll_clist_first_insert(1, &l);
        ASSERT_EQ(ll_clist_next(l), l);
        ASSERT_EQ(ll_clist_data(l), 1);
        ll_clist_remove_all(&l);
    }

    TEST_F(CircularLinkedListTest, InsertingAfter) {
        ll_clist_first_insert(1, &l);
        ll_clist_insert_after(2, l);

        ASSERT_EQ(ll_clist_data(ll_clist_next(l)), 2);
        ASSERT_EQ(ll_clist_data(ll_clist_next(ll_clist_next(l))), 1);
        ll_clist_remove_all(&l);
    }

    TEST_F(CircularLinkedListTest, RemovingEveryElements) {
        ll_clist_first_insert(1, &l);
        ll_clist_insert_after(2, l);

        ll_clist_remove_all(&l);
        ASSERT_EQ(l, nullptr);
    }

    TEST_F(CircularLinkedListTest, InsertingBefore) {
        ll_clist_first_insert(1, &l);
        ll_clist_insert_before(2, l);
        ll_clist_insert_before(3, l);
        ll_clist_insert_before(4, l);
        ll_clist_insert_before(5, l);

        ASSERT_EQ(ll_clist_data(l), 1);
    }
}