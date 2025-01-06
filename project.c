// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <string.h>
// #include <curl/curl.h>
// #include <ctype.h>
// #include <time.h>

// #define ALPHABET_COUNT 26

// // Global variables
// int word_char_count[ALPHABET_COUNT] = {0};
// pthread_mutex_t lock;

// // Structure for thread arguments
// typedef struct {
//     char **urls;
//     int start_idx;
//     int end_idx;
//     int max_words;
// } thread_arg_t;

// // Function to fetch webpage content using libcurl
// size_t write_callback(void *contents, size_t size, size_t nmemb, char **output) {
//     size_t total_size = size * nmemb;
//     char *temp = realloc(*output, strlen(*output) + total_size + 1);
//     if (temp == NULL) return 0; // Out of memory
//     *output = temp;
//     strncat(*output, contents, total_size);
//     return total_size;
// }

// char* fetch_webpage(const char *url) {
//     CURL *curl = curl_easy_init();
//     if (!curl) return NULL;

//     char *output = malloc(1);
//     if (!output) return NULL;
//     *output = '\0';

//     curl_easy_setopt(curl, CURLOPT_URL, url);
//     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
//     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
//     curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);

//     CURLcode res = curl_easy_perform(curl);
//     if (res != CURLE_OK) {
//         fprintf(stderr, "Curl error: %s\n", curl_easy_strerror(res));
//         free(output);
//         curl_easy_cleanup(curl);
//         return NULL;
//     }

//     curl_easy_cleanup(curl);
//     return output;
// }

// // Function to count words starting with each alphabet
// void count_words(const char *text, int max_words) {
//     char *copy = strdup(text);
//     if (!copy) return;

//     int local_word_count[ALPHABET_COUNT] = {0};
//     char *word = strtok(copy, " \t\n\r.,;:!?\"()[]{}");
//     int counter = 0;

//     while (word != NULL) {
//         if (isalpha(word[0])) {
//             int index = tolower(word[0]) - 'a';
//             if(index<26 && index>-1)
//             {
//               local_word_count[index]++;
//             }
//         }
//         counter++;

//         if (counter == max_words) {
//             pthread_mutex_lock(&lock);
//             for (int i = 0; i < ALPHABET_COUNT; i++) {
//                 word_char_count[i] += local_word_count[i];
//             }
//             pthread_mutex_unlock(&lock);
//             memset(local_word_count, 0, sizeof(local_word_count));
//             counter = 0;
//         }
//         word = strtok(NULL, " \t\n\r.,;:!?\"()[]{}");
//     }

//     pthread_mutex_lock(&lock);
//     for (int i = 0; i < ALPHABET_COUNT; i++) {
//         word_char_count[i] += local_word_count[i];
//     }
//     pthread_mutex_unlock(&lock);

//     free(copy);
// }

// // Thread function
// void *process_urls(void *arg) {
//     thread_arg_t *args = (thread_arg_t *)arg;

//     for (int i = args->start_idx; i < args->end_idx; i++) {
//         char *content = fetch_webpage(args->urls[i]);
//         if (content) {
//             count_words(content, args->max_words);
//             free(content);
//         } else {
//             fprintf(stderr, "Failed to fetch URL: %s\n", args->urls[i]);
//         }
//     }
//     return NULL;
// }

// int main(int argc, char *argv[]) {

//     struct timespec start, end;
//     clock_gettime(CLOCK_MONOTONIC, &start);

//     if (argc != 4) {
//         fprintf(stderr, "Usage: %s <url_file> <num_threads> <X>\n", argv[0]);
//         return EXIT_FAILURE;
//     }

    
//     char *url_file = argv[1];
//     int num_threads = atoi(argv[2]);
//     int max_words = atoi(argv[3]);

//     FILE *file = fopen(url_file, "r");
//     if (!file) {
//         perror("Error opening file");
//         return EXIT_FAILURE;
//     }

//     char **urls = NULL;
//     int url_count = 0;
//     size_t capacity = 0;
//     char line[1024];

//     while (fgets(line, sizeof(line), file)) {
//         line[strcspn(line, "\n")] = '\0';
//         if (url_count >= capacity) {
//             capacity = capacity ? capacity * 2 : 16;
//             urls = realloc(urls, capacity * sizeof(char *));
//             if (!urls) {
//                 perror("Memory allocation error");
//                 fclose(file);
//                 return EXIT_FAILURE;
//             }
//         }
//         urls[url_count++] = strdup(line);
//     }
//     fclose(file);

//     pthread_mutex_init(&lock, NULL);

//     pthread_t threads[num_threads];
//     thread_arg_t thread_args[num_threads];

//     for (int i = 0; i < num_threads; i++) {
//         thread_args[i].urls = urls;
//         thread_args[i].start_idx = i * (url_count / num_threads);
//         thread_args[i].end_idx = (i == num_threads - 1) ? url_count : (i + 1) * (url_count / num_threads);
//         thread_args[i].max_words = max_words;

//         pthread_create(&threads[i], NULL, process_urls, &thread_args[i]);
//     }

//     for (int i = 0; i < num_threads; i++) {
//         pthread_join(threads[i], NULL);
//     }

//     pthread_mutex_destroy(&lock);

//     for (int i = 0; i < ALPHABET_COUNT; i++) {
//         printf("%c: %d\n", 'A' + i, word_char_count[i]);
//     }

//     for (int i = 0; i < url_count; i++) {
//         free(urls[i]);
//     }
//     free(urls);

//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
//     printf("Operation time: %f seconds\n", elapsed);
//     // printf("%f", elapsed);


//     return EXIT_SUCCESS;
// }




#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <curl/curl.h>
#include <ctype.h>
#include <time.h>

#define ALPHABET_COUNT 26

// Global variables
int word_char_count[ALPHABET_COUNT] = {0};
pthread_mutex_t lock;

// Structure for thread arguments
typedef struct {
    char **urls;
    int start_idx;
    int end_idx;
    int max_words;
    int thread_num;
} thread_arg_t;

// Function to fetch webpage content using libcurl
size_t write_callback(void *contents, size_t size, size_t nmemb, char **output) {
    size_t total_size = size * nmemb;
    char *temp = realloc(*output, strlen(*output) + total_size + 1);
    if (temp == NULL) return 0; // Out of memory
    *output = temp;
    strncat(*output, contents, total_size);
    return total_size;
}

char* fetch_webpage(const char *url) {
    CURL *curl = curl_easy_init();
    if (!curl) return NULL;

    char *output = malloc(1);
    if (!output) return NULL;
    *output = '\0';

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Curl error: %s\n", curl_easy_strerror(res));
        free(output);
        curl_easy_cleanup(curl);
        return NULL;
    }

    curl_easy_cleanup(curl);
    return output;
}

// Function to count words starting with each alphabet
void count_words(const char *text, int max_words) {
    char *copy = strdup(text);
    if (!copy) return;

    int local_word_count[ALPHABET_COUNT] = {0};
    char *word = strtok(copy, " \t\n\r.,;:!?\"()[]{}");
    int counter = 0;

    while (word != NULL) {
        if (isalpha(word[0])) {
            int index = tolower(word[0]) - 'a';
            if(index < 26 && index > -1) {
                local_word_count[index]++;
            }
        }
        counter++;

        if (counter == max_words) {
            pthread_mutex_lock(&lock);
            for (int i = 0; i < ALPHABET_COUNT; i++) {
                word_char_count[i] += local_word_count[i];
            }
            pthread_mutex_unlock(&lock);
            memset(local_word_count, 0, sizeof(local_word_count));
            counter = 0;
        }
        word = strtok(NULL, " \t\n\r.,;:!?\"()[]{}");
    }

    pthread_mutex_lock(&lock);
    for (int i = 0; i < ALPHABET_COUNT; i++) {
        word_char_count[i] += local_word_count[i];
    }
    pthread_mutex_unlock(&lock);

    free(copy);
}

// Thread function
// void *process_urls(void *arg) {
//     thread_arg_t *args = (thread_arg_t *)arg;
//     struct timespec start, end;
//     for (int i = args->start_idx; i < args->end_idx; i++) {
//         clock_gettime(CLOCK_MONOTONIC, &start);
        
//         char *content = fetch_webpage(args->urls[i]);

//         clock_gettime(CLOCK_MONOTONIC, &end);
//         double url_read_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
//         printf("\nThread No %d Url No %d time taken for geting text %f\n",args->thread_num,(i+1),url_read_time);


//         if (content) {
//             count_words(content, args->max_words);
//             free(content);
//         } else {
//             fprintf(stderr, "Failed to fetch URL: %s\n", args->urls[i]);
//         }
//     }
//     return NULL;
// }


void *process_urls(void *arg) {
    thread_arg_t *args = (thread_arg_t *)arg;
    struct timespec thread_start, thread_end, start, end;
    double total_thread_time = 0.0;

    clock_gettime(CLOCK_MONOTONIC, &thread_start); // Start timing for the thread

    for (int i = args->start_idx; i < args->end_idx; i++) {
        zclock_gettime(CLOCK_MONOTONIC, &start); // Start timing for a single URL fetch

        char *content = fetch_webpage(args->urls[i]);

        clock_gettime(CLOCK_MONOTONIC, &end); // End timing for a single URL fetch
        double url_fetch_time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\nThread No %d: URL No %d, Time taken for fetching text: %f seconds\n", args->thread_num, i + 1, url_fetch_time);

        total_thread_time += url_fetch_time; // Accumulate time taken for all URL fetches in this thread

        if (content) {
            count_words(content, args->max_words);
            free(content);
        } else {
            fprintf(stderr, "Thread No %d: Failed to fetch URL: %s\n", args->thread_num, args->urls[i]);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &thread_end); // End timing for the thread
    double thread_execution_time = (thread_end.tv_sec - thread_start.tv_sec) + (thread_end.tv_nsec - thread_start.tv_nsec) / 1e9;

    printf("\nThread No %d Total Execution Time: %f seconds (Total URL Fetch Time: %f seconds)\n", 
           args->thread_num, thread_execution_time, total_thread_time);

    return NULL;
}



int main(int argc, char *argv[]) {
    struct timespec start, end, op_start, op_end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <url_file> <num_threads> <X>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *url_file = argv[1];
    int num_threads = atoi(argv[2]);
    int max_words = atoi(argv[3]);

    FILE *file = fopen(url_file, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Time URL file reading
    clock_gettime(CLOCK_MONOTONIC, &op_start);
    char **urls = NULL;
    int url_count = 0;
    size_t capacity = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (url_count >= capacity) {
            capacity = capacity ? capacity * 2 : 16;
            urls = realloc(urls, capacity * sizeof(char *));
            if (!urls) {
                perror("Memory allocation error");
                fclose(file);
                return EXIT_FAILURE;
            }
        }
        urls[url_count++] = strdup(line);
    }
    fclose(file);
    clock_gettime(CLOCK_MONOTONIC, &op_end);
    double file_read_time = (op_end.tv_sec - op_start.tv_sec) + (op_end.tv_nsec - op_start.tv_nsec) / 1e9;
    

    // Time URL processing
    pthread_mutex_init(&lock, NULL);

    pthread_t threads[num_threads];
    thread_arg_t thread_args[num_threads];

    clock_gettime(CLOCK_MONOTONIC, &op_start);
    for (int i = 0; i < num_threads; i++) {
        thread_args[i].urls = urls;
        thread_args[i].thread_num = (i+1);
        thread_args[i].start_idx = i * (url_count / num_threads);
        thread_args[i].end_idx = (i == num_threads - 1) ? url_count : (i + 1) * (url_count / num_threads);
        thread_args[i].max_words = max_words;

        pthread_create(&threads[i], NULL, process_urls, &thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &op_end);
    double thread_process_time = (op_end.tv_sec - op_start.tv_sec) + (op_end.tv_nsec - op_start.tv_nsec) / 1e9;
   

    pthread_mutex_destroy(&lock);

    // // Print word count results
    // for (int i = 0; i < ALPHABET_COUNT; i++) {
    //     printf("%c: %d\n", 'A' + i, word_char_count[i]);
    // }

    // Free memory for URLs
    for (int i = 0; i < url_count; i++) {
        free(urls[i]);
    }
    free(urls);

    // Time overall execution
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;



    printf("\nTime for reading URL file: %f seconds\n", file_read_time);
    printf("\nTime for processing Threads: %f seconds\n", thread_process_time);
    printf("\nTotal operation time: %f seconds\n", elapsed);

    return EXIT_SUCCESS;
}
