#include <string>
#include <algorithm>

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
    // following given pseudocode
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        // create dummy node
        ListNode* dummyHead = new ListNode;
        // set currNode to dummy
        ListNode* currNode = dummyHead;
        int carry{0};
        ListNode* p{l1}, *q{l2};

        // keep going until the end of both lists are reached
        while (p || q)
        {
            // value should be 0 is end of list is reached
            int x = p ? p->val : 0;
            int y = q ? q->val : 0;
            int sum = x + y + carry; // anywhere from 0 to 19
            carry  = sum / 10; // either 0 or 1

            // node creation
            ListNode* newNode = new ListNode(sum % 10);
            // add node
            currNode->next = newNode;
            // advance list
            currNode = currNode->next;

            // advance until end (nullptr) is reached
            if (p)
            { p = p->next; }
            if (q)
            { q = q->next; }
        }

        // gotta make a node for the '1' sometimes
        if (carry)
        {
            // node creation
            ListNode* newNode = new ListNode(carry);
            // add node
            currNode->next = newNode;
            // advance list
            currNode = currNode->next;
        }
        return dummyHead->next;
    }
	
	// my own mad method that didn't even work
	size_t unreverseNumber(size_t n, bool hasLeading0)
    {
        std::string s{std::to_string(n)};
        size_t result{0};
        std::reverse(s.begin(), s.end());
        for (char x : s)
        {
            result = result * 10 + (x - '0');
        }
        if (hasLeading0)
        {
            result *= 10;
        }
        return result;
    }

    // NONONONONONONONONONONONONONONONONONONONONONONONO
    ListNode* addTwoNumbers0(ListNode* l1, ListNode* l2)
    {
        size_t n1{0}, n2{0}, n3;
        bool n1First{true}, n2First{true};
        bool n1HasLeading0{false}, n2HasLeading0{false};

        // get reversed numbers
        while(l1 != nullptr)
        {
            if(n1First && l1->val == 0)
            { n1HasLeading0 = true; }

            if (n1First)
            { n1First = false; }

            n1 = n1 * 10 + l1->val;
            l1 = l1->next;
        }
        // std::cout << n1 <<'\n';

        while(l2 != nullptr)
        {
            if(n2First && l2->val == 0)
            { n2HasLeading0 = true; }

            if (n2First)
            { n2First = false; }

            n2 = n2 * 10 + l2->val;
            l2 = l2->next;
        }
        // std::cout << n2 <<'\n';

        // unreverse numbers
        n1 = unreverseNumber(n1, n1HasLeading0);
        n2 = unreverseNumber(n2, n2HasLeading0);
        // std::cout << n1 <<'\n';
        // std::cout << n2 <<'\n';

        // add
        n3 = n1 + n2;

        // create LL
        std::string s{std::to_string(n3)}; // '8', '0', '7', '\0'
        ListNode* head;
        for (int i{0}; i < s.length(); ++i)
        {
            if (!i)
            {
                ListNode* end = new ListNode(s[i] - '0');
                head = end;
                continue;
            }
            ListNode* newNode = new ListNode(s[i] - '0', head);
            head = newNode;
        }
        return head;
    }
};
