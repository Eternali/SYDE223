class Solution:
    def intersection(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        uniq1 = set(nums1)
        uniq2 = set(nums2)
        return [ n for n in uniq2 if n in uniq1 ]