import java.util.*;

/**
 * QuickSort
 */
public class QuickSort {

    private static void swap(int[] arr, int i, int j) {

        int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
    }
    
    private static void qs(int[] arr, int lo, int hi) {

        if (lo >= hi) return;

        int i = lo, j = hi, mi = arr[i+j >> 1];
        while (i <= j) {
            while (arr[i] < mi) i++;
            while (arr[j] > mi) j--;
            if (i <= j) {
                swap(arr, i, j);
                i++;
                j--;
            }
        }
        qs(arr, lo, j);
        qs(arr, i, hi);
    }
    public static int[] qsort(int[] arr) {

        if (arr == null) return null;

        qs(arr, 0, arr.length-1);

        return arr;
    }
    public static void main(String[] args) {
        
        final int n = 5;
        int[] arr = new int[n];
        Random rd = new Random();

        for (int i = 0; i < n; i++) {
            arr[i] = rd.nextInt(100);
        }
        
        System.out.println("random array: " + Arrays.toString(arr));
        qsort(arr);
        System.out.println("ordered array: " + Arrays.toString(arr));
    }
}