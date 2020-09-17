/**
 * SortAndSearch
 */
import java.util.*;

public class SortAndSearch {

    public static void main(String[] args) {
        
        int[] arr = { 12, 45, 67, 89, 123, -45, 67 };
        
        QuickSort.qsort(arr);

        System.out.println(Arrays.toString(arr));

        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextInt()) {
            int key = scanner.nextInt();
            int index = Arrays.binarySearch(arr, key);
            if (index < 0 || arr[index] != key) System.out.println("no");
            else System.out.println("yes");
        }
    }
}