struct ListNode // Definition for singly-linked list.
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // printf("starting\n");
        // empty list cases
        if (!list1) { return list2; }
        if (!list2) { return list1; }
        
        // setting first node of result
        ListNode* result;
        if (list1->val < list2->val)
        {
            result = list1;
            // advance list1 since we took the 
            // the 1st node from there
            list1 = list1->next;
        }
        else
        {
            result = list2;
            list2 = list2->next;
        }
        
        ListNode* current{result};
        // loop until a list has reached its end
        while (list1 && list2)
        {
            // set the next node in the list
            // advance the list that the node was taken from
            // advance the `current` to the next node
            if (list1->val < list2->val)
            {
                current->next = list1;
                list1 = list1->next;
            }
            else
            {
                current->next = list2;
                list2 = list2->next;
            }
            current = current->next;
        }
        
        // include the reminaing elements of
        // the list that didn't end yet
        current->next = !list1 ? list2 : list1;
        
        return result;
    }
};
