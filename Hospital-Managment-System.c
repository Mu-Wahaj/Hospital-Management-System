#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 100
#define MAX_STAFF 100
#define NAME_LEN 100
#define BLOOD_LEN 10
#define GENDER_LEN 10
#define POSITION_LEN 50

typedef struct {
    int id;
    char name[NAME_LEN];
    int age;
    char bloodGroup[BLOOD_LEN];
    char gender[GENDER_LEN];
} Patient;

typedef struct {
    int id;
    char name[NAME_LEN];
    char position[POSITION_LEN];
} Staff;

Patient patients[MAX_PATIENTS];
int patientCount = 0;
Staff staffMembers[MAX_STAFF];
int staffCount = 0;

void loadPatients() {
    FILE *file = fopen("patients.txt", "r");
    if (!file) return;
    while (fscanf(file, "%d\n", &patients[patientCount].id) == 1) {
        fgets(patients[patientCount].name, NAME_LEN, file);
        patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = 0;
        fscanf(file, "%d\n", &patients[patientCount].age);
        fgets(patients[patientCount].bloodGroup, BLOOD_LEN, file);
        patients[patientCount].bloodGroup[strcspn(patients[patientCount].bloodGroup, "\n")] = 0;
        fgets(patients[patientCount].gender, GENDER_LEN, file);
        patients[patientCount].gender[strcspn(patients[patientCount].gender, "\n")] = 0;
        patientCount++;
        if (patientCount >= MAX_PATIENTS) break;
    }
    fclose(file);
}

void savePatients() {
    FILE *file = fopen("patients.txt", "w");
    if (!file) return;
    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d\n%s\n%d\n%s\n%s\n",
            patients[i].id, patients[i].name, patients[i].age,
            patients[i].bloodGroup, patients[i].gender);
    }
    fclose(file);
}

void loadStaff() {
    FILE *file = fopen("staff.txt", "r");
    if (!file) return;
    while (fscanf(file, "%d\n", &staffMembers[staffCount].id) == 1) {
        fgets(staffMembers[staffCount].name, NAME_LEN, file);
        staffMembers[staffCount].name[strcspn(staffMembers[staffCount].name, "\n")] = 0;
        fgets(staffMembers[staffCount].position, POSITION_LEN, file);
        staffMembers[staffCount].position[strcspn(staffMembers[staffCount].position, "\n")] = 0;
        staffCount++;
        if (staffCount >= MAX_STAFF) break;
    }
    fclose(file);
}

void saveStaff() {
    FILE *file = fopen("staff.txt", "w");
    if (!file) return;
    for (int i = 0; i < staffCount; i++) {
        fprintf(file, "%d\n%s\n%s\n",
            staffMembers[i].id, staffMembers[i].name, staffMembers[i].position);
    }
    fclose(file);
}

void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient list full!\n");
        return;
    }
    printf("Enter Patient ID: ");
    scanf("%d", &patients[patientCount].id); getchar();
    printf("Enter Patient Name: ");
    fgets(patients[patientCount].name, NAME_LEN, stdin);
    patients[patientCount].name[strcspn(patients[patientCount].name, "\n")] = 0;
    printf("Enter Patient Age: ");
    scanf("%d", &patients[patientCount].age); getchar();
    printf("Enter Blood Group: ");
    fgets(patients[patientCount].bloodGroup, BLOOD_LEN, stdin);
    patients[patientCount].bloodGroup[strcspn(patients[patientCount].bloodGroup, "\n")] = 0;
    printf("Enter Gender (M/F): ");
    fgets(patients[patientCount].gender, GENDER_LEN, stdin);
    patients[patientCount].gender[strcspn(patients[patientCount].gender, "\n")] = 0;
    patientCount++;
    savePatients();
    printf("Patient added successfully!\n");
}

void addStaff() {
    if (staffCount >= MAX_STAFF) {
        printf("Staff list full!\n");
        return;
    }
    printf("Enter Staff ID: ");
    scanf("%d", &staffMembers[staffCount].id); getchar();
    printf("Enter Staff Name: ");
    fgets(staffMembers[staffCount].name, NAME_LEN, stdin);
    staffMembers[staffCount].name[strcspn(staffMembers[staffCount].name, "\n")] = 0;
    printf("Enter Position: ");
    fgets(staffMembers[staffCount].position, POSITION_LEN, stdin);
    staffMembers[staffCount].position[strcspn(staffMembers[staffCount].position, "\n")] = 0;
    staffCount++;
    saveStaff();
    printf("Staff added successfully!\n");
}

void displayPatients() {
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d | Name: %s | Age: %d | Blood Group: %s | Gender: %s\n",
            patients[i].id, patients[i].name, patients[i].age,
            patients[i].bloodGroup, patients[i].gender);
    }
}

void displayStaff() {
    for (int i = 0; i < staffCount; i++) {
        printf("Staff ID: %d | Name: %s | Position: %s\n",
            staffMembers[i].id, staffMembers[i].name, staffMembers[i].position);
    }
}

void searchPatientByID(int id, int index) {
    if (index >= patientCount) {
        printf("Patient not found!\n");
        return;
    }
    if (patients[index].id == id) {
        printf("ID: %d | Name: %s | Age: %d | Blood Group: %s | Gender: %s\n",
            patients[index].id, patients[index].name, patients[index].age,
            patients[index].bloodGroup, patients[index].gender);
    } else {
        searchPatientByID(id, index + 1);
    }
}

void searchStaffByID(int id, int index) {
    if (index >= staffCount) {
        printf("Staff not found!\n");
        return;
    }
    if (staffMembers[index].id == id) {
        printf("Staff ID: %d | Name: %s | Position: %s\n",
            staffMembers[index].id, staffMembers[index].name, staffMembers[index].position);
    } else {
        searchStaffByID(id, index + 1);
    }
}

void deletePatient() {
    int id, found = 0;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < patientCount - 1; j++)
                patients[j] = patients[j + 1];
            patientCount--;
            savePatients();
            printf("Patient record deleted.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Patient not found!\n");
}

void deleteStaff() {
    int id, found = 0;
    printf("Enter Staff ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < staffCount; i++) {
        if (staffMembers[i].id == id) {
            for (int j = i; j < staffCount - 1; j++)
                staffMembers[j] = staffMembers[j + 1];
            staffCount--;
            saveStaff();
            printf("Staff record deleted.\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Staff not found!\n");
}

void generateReport() {
    printf("Generating Report...\n");
    printf("Patients Report:\n");
    displayPatients();
    printf("Staff Report:\n");
    displayStaff();
}

void billingSystem() {
    int id;
    printf("Enter Patient ID for Billing: ");
    scanf("%d", &id);
    printf("Billing for patient ID %d completed.\n", id);
}

void manageAppointments() {
    char date[30], time[30];
    int patientID;
    printf("Enter Appointment Date: ");
    getchar();
    fgets(date, 30, stdin);
    date[strcspn(date, "\n")] = 0;
    printf("Enter Appointment Time: ");
    fgets(time, 30, stdin);
    time[strcspn(time, "\n")] = 0;
    printf("Enter Patient ID: ");
    scanf("%d", &patientID);
    printf("Appointment scheduled for Patient ID %d on %s at %s\n", patientID, date, time);
}

void showCurrentDateTime() {
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    printf("Current date and time: %d-%02d-%02d %02d:%02d:%02d\n",
        1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday,
        ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
}

void managePatientMenu() {
    int choice;
    while (1) {
        printf("-----------------------------------------------\n");
        printf("            PATIENT MANAGEMENT MODULE           \n");
        printf("-----------------------------------------------\n");
        printf("1. Add New Patient\n");
        printf("2. View Patient List\n");
        printf("3. Search Patient by ID\n");
        printf("4. Delete Patient Record\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) addPatient();
        else if (choice == 2) displayPatients();
        else if (choice == 3) {
            int id;
            printf("Enter Patient ID: ");
            scanf("%d", &id);
            searchPatientByID(id, 0);
        }
        else if (choice == 4) deletePatient();
        else if (choice == 5) return;
        else printf("Invalid choice!\n");
    }
}

void manageStaffMenu() {
    int choice;
    while (1) {
        printf("-----------------------------------------------\n");
        printf("            STAFF MANAGEMENT MODULE            \n");
        printf("-----------------------------------------------\n");
        printf("1. Add New Staff\n");
        printf("2. View Staff List\n");
        printf("3. Search Staff by ID\n");
        printf("4. Delete Staff Record\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1) addStaff();
        else if (choice == 2) displayStaff();
        else if (choice == 3) {
            int id;
            printf("Enter Staff ID: ");
            scanf("%d", &id);
            searchStaffByID(id, 0);
        }
        else if (choice == 4) deleteStaff();
        else if (choice == 5) return;
        else printf("Invalid choice!\n");
    }
}

void showMenu() {
    printf("-----------------------------------------------\n");
    printf("       WELCOME TO THE HOSPITAL MANAGEMENT SYSTEM       \n");
    printf("-----------------------------------------------\n");
    printf("1. Manage Patients\n");
    printf("2. Manage Appointments\n");
    printf("3. Billing System\n");
    printf("4. View Reports\n");
    printf("5. Manage Staff\n");
    printf("6. Show Current Date and Time\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    loadPatients();
    loadStaff();
    int choice;
    while (1) {
        showMenu();
        scanf("%d", &choice);
        if (choice == 1) managePatientMenu();
        else if (choice == 2) manageAppointments();
        else if (choice == 3) billingSystem();
        else if (choice == 4) generateReport();
        else if (choice == 5) manageStaffMenu();
        else if (choice == 6) showCurrentDateTime();
        else if (choice == 7) {
            printf("Exiting the system.\n");
            break;
        }
        else printf("Invalid choice!\n");
    }
    return 0;
}
