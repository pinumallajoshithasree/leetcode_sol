class Solution {
    public boolean canWePlace(int[] arr,int dist,int cows){
         int count=1;
         int lastPos=arr[0];
         for(int i=0;i<arr.length;i++){
             if(arr[i]-lastPos>=dist){
                 count++;
                 lastPos=arr[i];
             }
         }
         return (count>=cows);
          
    }
    //bruteforce
    // public int aggressiveCows(int[] arr, int k) {
    //     // code here
    //     Arrays.sort(arr);
    //     int n=arr.length;
    //     int maxDist=arr[n-1]-arr[0];
    //     for(int d=1;d<=maxDist;d++){
    //         if(!canWePlace(arr,d,k))
    //           return d-1;
    //     }
    //      return maxDist;
    // }

  //optimal
  public int aggressiveCows(int[] arr, int k) {
         Arrays.sort(arr);
         int n=arr.length;
         int maxDist=arr[n-1]-arr[0];
         int low=0;
         int high=maxDist;
         int ans=0;
         while(low<=high){
             int mid=(low+high)/2;
             if(canWePlace(arr,mid,k)){
                 ans=mid;
                 low=mid+1;
             }
             else
               high=mid-1;
         }
         return ans;
        
    }
}
