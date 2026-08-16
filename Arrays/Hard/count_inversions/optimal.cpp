class Solution {
    void merge(vector<int>& nums,int low,int mid,int high){
              int i=low;
              int j=mid+1;
              vector<int> temp;
              while(i<=mid && j<=high){
                if(nums[i]<=nums[j]){
                    temp.push_back(nums[i++]);
                }
                else{
                    temp.push_back(nums[j++]);
                }
              }

              while(i<=mid){
                 temp.push_back(nums[i++]);
              }
              while(j<=high){
                 temp.push_back(nums[j++]);
              }
              for(int i=low;i<=high;i++){
                nums[i]=temp[i-low];
              }
       }
       int countPairs(vector<int>& nums,int low,int mid,int high){
          int c=0;
          int j=mid+1;
          for(int i=low;i<=mid;i++){
              while(j<=high && nums[i]> (long long)2*nums[j]){
                j++;
              }
              c+=(j-(mid+1));
          }
          return c;
       }
       int ms(vector<int>& nums,int low,int high){
         int c=0;
          if(low<high){
              int mid=(low+high)/2;
              c+=ms(nums,low,mid);
              c+=ms(nums,mid+1,high);
              c+=countPairs(nums,low,mid,high);
              merge(nums,low,mid,high);
          }
          return c;
       }

public:
    int reversePairs(vector<int>& nums) {
       return ms(nums,0,nums.size()-1);
    }
};

// Complexity Analysis

// Time Complexity: O(2N*logN), Inside the mergeSort() we call merge() and countPairs() except mergeSort() itself. Now, inside the function countPairs(), though we are running a nested loop, we are actually iterating the left half once and the right half once in total. That is why, the time complexity is O(N). And the merge() function also takes O(N). The mergeSort() takes O(logN) time complexity. Therefore, the overall time complexity will be O(logN * (N+N)) = O(2N*logN).

// Space Complexity: O(N), as in the merge sort We use a temporary array to store elements in sorted order.
