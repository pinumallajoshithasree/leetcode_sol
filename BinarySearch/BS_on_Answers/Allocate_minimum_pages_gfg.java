// For every binary-search iteration, CountStudents() takes O(n).

// Number of iterations = O(log S).

// Therefore:

// Time Complexity = O(n × log S)
// Sc:O(1)

class Solution {
    public int CountStudents(int[] arr,long pages){
        int count=1;
        long spages=0;
        for(int i=0;i<arr.length;i++){
            if(spages+arr[i]<=pages)
                  spages+=arr[i];
            else{
                count++;
                spages=arr[i];
            }
        }
        return count;
    }
    public int findPages(int[] arr, int k) {
        // code here
        int n=arr.length;
        if(k>n) return -1;
        long low=Arrays.stream(arr).max().getAsInt(); //to get max value from array
        long high=Arrays.stream(arr).asLongStream().sum();
        while(low<=high){
            long mid=(low+high)/2;
            int students=CountStudents(arr,mid);
            if(students>k){
                low=mid+1;
            }
            else
              high=mid-1;
        }
        return (int)low;
        
    }
}
