#include <stdio.h>
#include <omp.h>

/**
 * This method prints the header as the first line of the console output.
 */
void print_header() {
    printf("%s%17s\n","Bucket#", "Histogram");
}

/**
 * This method handles printing the number of *'s needed for the histogram.
 * @param n - the number of stars to print
 */
void print_bars(int n) {
    for(int j = 1; j<= n; j++) {
        // print the asterisk bar...repeat...
        printf("*");
    }
    // go to new line for new row...repeats...
    printf("\n");
}

/**
 * Calculates the width of each bucket for the histogram.
 *
 * @param min_meas - the minimum value a bucket can hold
 * @param max_meas - the maximum value a bucket can hold
 * @param bucket_count - the number of desired buckets
 * @return the range of items assigned to a bucket
 */
int calculate_bucket_width(int min_meas, int max_meas, int bucket_count) {
    return (max_meas - min_meas) / bucket_count;
}

/**
 * This program prints a histogram.
 *
 * Reference: http://java-samples.com/showtutorial.php?tutorialid=1576
 * @return the exit code indicating program success or failure.
 */
int main() {
    // input variables
    /**
     * The number of elements the program will process on
     * a given run.
     */
    int num_data_elements = 0;
    /**
     * The data input by the user. This is the data that will
     * be counted for each bucket.
     */
    float data[num_data_elements];
    /**
     * The minimum value that a bucket can have on this run.
     * These will be integer numbers so they are rounded.
     * This makes sense when considering bounds for floats.
     */
    int min_meas;
    /**
     * The maximum value that a bucket can have on this run.
     * These will be integer numbers so they are rounded.
     * This makes sense when considering bounds for floats.
     */
    int max_meas;
    /**
     * The number of buckets that will be used for this
     * histogram. This is the number of bar graphs that
     * will be generated as well.
     */
    int bucket_count;

    // output variables
    /**
     * This is the array of upper bounds for each bucket
     */
    float bucket_maxes[bucket_count];
    /**
     * These values are the counts for each bucket.
     * The elements in this array can be used to generate
     * the bars for each grouping.
     */
    int bucket_counts[bucket_count];
    /**
     * The range of values that each bucket can hold.
     */
    int bucket_width = 0;

    // accept inputs: number of data elements, data elements
    // minimum and maximum value
    // number of bins
    printf("Please input the number of data elements: \n");
    scanf("%d", &num_data_elements);
    printf("Please input the data elements: \n");
    for(int i = 0; i < num_data_elements; i++) {
        scanf("%f", &data[i]);
        printf("You entered: %f\n", data[i]);
    }
    printf("Please enter the minimum data value for a bucket: \n");
    scanf("%d", &min_meas);
    printf("Please enter the maximum data value for a bucket: \n");
    scanf("%d", &max_meas);
    printf("Please enter the number of buckets: \n");
    scanf("%d", &bucket_count);

    // calculate the bucket width
    bucket_width = calculate_bucket_width(min_meas, max_meas, bucket_count);
    printf("The bucket width is: %d\n", bucket_width);

    // initialize the bin_maxes
    for (int b = 0; b < bucket_count; b++) {
        bucket_maxes[b] = min_meas + bucket_width * (b+1);
        printf("The bucket_max for bucket %d is %f: \n", b, bucket_maxes[b]);
    }

    // initialize bucket_counts
    for (int b = 0; b < bucket_count; b++) {
        bucket_counts[b] = 0;
    }

    // do the counting
    for (int d = 0; d < num_data_elements; d++) {
        for (int m = 0; m < bucket_count; m++) {
            if (data[d] >= min_meas && data[d] < bucket_maxes[m]) {
                bucket_counts[m]++;
                printf("Value of the bucket_count: %i\n", bucket_counts[m]);

                // Once a value is added, we only want to add that value once.
                // So, the loop needs to end a soon as it adds the value into a bucket.
                // This is a linear algorithm. It would be nice to make this binary.
                break;
            }
        }
    }

    // display the table header...
    print_header();
    // the outer for loop, read row by row...
    for(int i=0; i < bucket_count; i++) {
        printf("%d              ", i);
        // the inner for loop, for every row, read column by column and print the bar...
        print_bars(bucket_counts[i]);
    }
    return 0;
}

/* // A simple histogram for reference
#include <stdio.h>
#define  SIZE   10

int main()
{
       // declare and initialize an array named n with size SIZE...
       int n[SIZE] = {19, 3, 15, 7, 11, 9, 13, 5, 17, 1};
       int i, j;
       // display the table header...
       printf("%s%13s%17s\n","Element/index", "Value", "Histogram");
       // do the iteration...
       // the outer for loop, read row by row...
       for(i=0; i <= (SIZE-1); i++)
       {
              printf("%9d%15d       ", i, n[i]);
              // the inner for loop, for every row, read column by column and print the bar...
              for(j = 1; j<= n[i]; j++)
              // print the asterisk bar...repeat...
              printf("*");
              // go to new line for new row...repeats...
              printf("\n");
       }
       return   0;
}
 */