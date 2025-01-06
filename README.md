### README for Multithreaded Web Content Processing with Performance Profiling  

---

## Project Title  
**Performance Analysis and Optimization of Multithreaded Web Content Processing**  

---

## Project Description  
This project demonstrates an efficient multithreaded application for fetching, analyzing, and profiling web content. By dividing tasks into multiple threads, the application processes web pages in parallel, counts words starting with each alphabet, and records the time taken for various operations to identify performance bottlenecks.  

The application supports timing analysis for multiple configurations of threads and word-processing limits to evaluate the impact of concurrency and workload on performance.  

---

## Features  
- Fetches webpage content using **libcurl**.  
- Processes text to count the frequency of words starting with each alphabet (A-Z).  
- Implements multithreading for parallel execution using **pthreads**.  
- Profiles different operations, such as data fetching and text processing, to determine their time consumption.  
- Allows dynamic configuration of:  
  - **Number of Threads**: {1, 2, 4, 8}.  
  - **Words to Process per Chunk (X)**: {1, 32, 256, 1024, 4096}.  

---

## Requirements  
### Software Dependencies  
- **GCC Compiler**  
- **libcurl**  
- **pthreads**  

### Hardware Requirements  
- A system capable of running multithreaded applications.  
- Sufficient network access to fetch webpage data.  

---

## Setup Guide  

### Step 1: Clone or Download the Repository  
```bash  
git clone <repository-url>  
cd <repository-folder>  
```  

### Step 2: Install Dependencies  
Install `libcurl` using your package manager:  
```bash  
sudo apt-get install libcurl4-openssl-dev  # For Debian/Ubuntu  
sudo yum install libcurl-devel             # For CentOS/RedHat  
```  

### Step 3: Compile the Code  
```bash  
gcc -o web_processor web_processor.c -lcurl -lpthread  
```  

### Step 4: Prepare Input File  
Create a text file `urls.txt` containing a list of URLs, one per line:  
```text  
https://example.com  
https://example.org  
https://example.net  
```  

### Step 5: Run the Program  
```bash  
./web_processor urls.txt <num_threads> <max_words_per_chunk>  
```  
Example:  
```bash  
./web_processor urls.txt 4 1024  
```  

---

## Usage  

### Input Parameters  
1. **`<url_file>`**: Path to the text file containing the URLs.  
2. **`<num_threads>`**: Number of threads (e.g., 1, 2, 4, 8).  
3. **`<max_words_per_chunk>`**: Maximum words processed in each chunk (e.g., 1, 32, 256, 1024, 4096).  

### Output  
- The frequency of words starting with each letter (A-Z).  
- Timing information for the following operations:  
  - Total execution time.  
  - Time spent fetching data.  
  - Time spent processing text.  

---

## Timing Analysis  
The application profiles the following operations to identify performance bottlenecks:  
1. **Data Fetching**: Time taken to fetch webpage content using libcurl.  
2. **Text Processing**: Time taken to process text and count word frequencies.  
3. **Thread Management**: Overhead caused by creating and synchronizing threads.  

### Configuration Parameters  
- **Number of Threads (`<num_threads>`)**: {1, 2, 4, 8}.  
- **Words to Process per Chunk (`<max_words_per_chunk>`)**: {1, 32, 256, 1024, 4096}.  

The timing analysis helps identify the impact of multithreading and workload distribution on performance.  

---

## Example Results  

### Configuration:  
- **URLs**: 4  
- **Threads**: 2  
- **Words per Chunk**: 1024  

### Output (Sample):  
```text  
A: 45  
B: 32  
C: 78  
...  
Z: 12  

Timing Report:  
- Total Execution Time: 5.23 seconds  
- Data Fetching Time: 2.71 seconds  
- Text Processing Time: 2.18 seconds  
- Thread Management Time: 0.34 seconds  
```  

### Graph  
A graph of completion time vs. number of threads (for `X=1024`) is provided in the project directory as `graph.png`.  

---

## Optimization Steps  
1. **Reduced Mutex Locking**: Minimized the critical section to reduce contention between threads.  
2. **Chunked Processing**: Split text into chunks to balance workload among threads.  
3. **Dynamic Workload Allocation**: Adjusted URL-to-thread mapping for better load distribution.  

---

## Limitations  
- The performance gain is limited when the number of threads exceeds the number of URLs.  
- Network latency significantly impacts data-fetching time.  

---

## Future Enhancements  
- Implement URL validation and error handling.  
- Support for dynamic thread pools.  
- Add detailed logging and benchmarking tools.  

---

## License  
This project is licensed under the MIT License.  

---

## Author  
**Kifayat**  
Front-End Developer | Web Services Specialist  
