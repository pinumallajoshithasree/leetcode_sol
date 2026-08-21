// TC:(n log S)
// Sc:O(1)
class Solution {
    public int Count(int[] nums, long sum){
        int count=1;
        long Tsum=0;
        for(int i=0;i<nums.length;i++){
            if(Tsum+nums[i]>sum){
                count++;
                Tsum=nums[i];
            }
            else
              Tsum+=nums[i];
        }
        return count;
    }
    public int splitArray(int[] nums, int k) {
        // long low=Arrays.stream(nums).max().getAsInt();
        // long high=Arrays.stream(nums).asLongStream().sum();
        long low=0,high=0;
        for(int num: nums){
            high+=num;
            low= Math.max(low, num);
        }
        long res=-1;
        while(low<=high){
            long mid=(low+high)/2;
            int count=Count(nums,mid);
            if(count>k)
               low=mid+1;
            else{
               high=mid-1;
               res=mid;
            }
        }
        return (int)res;
    }
}
