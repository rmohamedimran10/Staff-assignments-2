#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Define a fixed-size structure for records
typedef struct {
    int id;
    char name[30];
    double salary;
} Employee;

int main() {
    const char *filename = "employees.dat";
    int fd;
    Employee emp1 = {1, "Alice", 50000.0};
    Employee emp2 = {2, "Bob", 60000.0};
    Employee emp_read;

    // 1. Creates a file securely using system calls
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    printf("Secure file created successfully.\n");

    // 2. Writes employee records
    write(fd, &emp1, sizeof(Employee));
    write(fd, &emp2, sizeof(Employee));
    printf("Initial employee records written.\n");

    // 3. Updates specific records without rewriting the entire file
    // Updating Bob's record (which is at index 1)
    Employee emp2_updated = {2, "Bob", 65500.0};
    lseek(fd, sizeof(Employee) * 1, SEEK_SET); 
    write(fd, &emp2_updated, sizeof(Employee));
    printf("Record 2 updated directly on disk.\n");

    // 4. Retrieves records from any location efficiently
    // Reading Bob's updated record back from disk
    lseek(fd, sizeof(Employee) * 1, SEEK_SET); 
    read(fd, &emp_read, sizeof(Employee));
    printf("Retrieved - ID: %d, Name: %s, Salary: %.2f\n", emp_read.id, emp_read.name, emp_read.salary);

    // Close the file descriptor
    close(fd);
    
    return 0;
}
