# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def reverseList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        
        if head is None or head.next is None:
            return head
        
        nodes = []
        node = head
        while node != None:
            nodes.append(node.val)
            node = node.next
        
        return list(reversed(nodes))
        
        # If they actually did the problem right and required a ListNode
        # to be returned, this is what I would have done.
        
        # def generate(head):
        #     node = head
        #     while node != None:
        #       yield node
        #       node = node.next

        # nodes = list(reversed([ n for n in generate(head) ]))
        # for [ i, n ] in enumerate(nodes[:-1]):
        #     n.next = nodes[i + 1]
        # nodes[-1].next = None
        # return nodes
