int array_sum1(int arr[], int size) {
  int sum = 0; 
  int i;
  for (i = 0; i < size; i++)
  sum += arr[i];
  return sum;
}

int array_sum2(int arr[], int size) {
  int sum1 = 0, sum2 = 0;
  int i;
  for (i = 0; i < size; i += 2) {
    sum1 += arr[i];
    sum2 += arr[i+1];
  }
  for (; i < size; i++)
    sum1 += arr[i];
  return sum1 + sum2;
}
