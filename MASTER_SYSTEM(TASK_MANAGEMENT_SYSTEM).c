#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

// task record  file :
#define TASK_FILE "tasks.bin"

//Console Dimensions:
#define CONSOLE_WIDTH 120

//Reset Code:
#define RESET "\x1b[0m"

//Text Styles:
#define BOLD "\x1b[1m"
#define BLINK "\x1b[5m"

//Foreground Colors:
#define RED_FG "\x1b[31m"
#define GREEN_FG "\x1b[32m"
#define YELLOW_FG "\x1b[33m"
#define BLUE_FG "\x1b[34m"
#define MAGENTA_FG "\x1b[35m"
#define CYAN_FG "\x1b[36m"
#define WHITE_FG "\x1b[37m"

//Bright Foreground Colors:
#define RED_BFG "\x1b[91m"
#define CYAN_BFG "\x1b[96m"
#define LIGHT_PINK_BFG "\x1b[95m"

//Background Colors:
#define BLUE_BG "\x1b[44m"
#define MAGENTA_BG "\x1b[45m"

//Bright Background Colors:
#define GREEN_BBG "\x1b[102m"
#define YELLOW_BBG "\x1b[103m"
#define CYAN_BBG "\x1b[106m"

//maximum number of tasks: 
#define MAX_TASKS 500
#define MAX_PROJECTS 100
#define MAX_USERS 100
#define MAX_COMMENTS 1000

//structure for task data type:
typedef struct 
{
char taskID[5]; 
char projectID[5];
char title[50];
char assigned_to[20];
char status[20];
char priority[20];
int is_used;
} 
Task;

//structure for project data type:
typedef struct Project
{
char ProjectID[5];
char ProjectName[29];
char ProjectDescription[76];
int is_used;	
}
Project;

//structure for user data type:
struct user 
{
char name[30];
char email[56];
int roll_no;
char id[5];
int is_used;
};

//structure for comment data type:
struct Comment 
{
char commentID[5];          
char taskID[5];             
char userID[5];             
char commentText[88];
int is_used;
};

//GLOBAL VARIABLES:

//1.task menu:
Task tasks[MAX_TASKS]={0};
int task_count=0;

//2.project menu:
int ProjectCount=0;
Project Projects[MAX_PROJECTS];

//3.user menu:
struct user users[MAX_USERS]; 
int user_count = 0;   

//4.comment menu:
struct Comment comments[MAX_COMMENTS];
int commentCount = 0;

//FUNCTION PROTOTYPES:
void display_welcomeScreen();
void display_mainMenu();
void loading_animation();

// Function Prototypes Task menu:
void display_taskMenu();
void addTask();
void updateTask();
void deleteTask();
void viewTask();
void listAllTasks();
void get_task_record(char task_id[5]);
void find_task_record();
int check_project_exists(char projectID[5]);
void delete_comments_by_taskID(char taskID[5]);
// by bubble sort logic
void sort_by_taskID(int order);
// by selection sort logic
void sort_by_title(int order);

// Function Prototypes Project menu:
void ShowProjectMenu();
void AddProject();
void DisplayProjects();
void SearchProject();
void SearchProjectByID();
void SearchProjectByName();
void UpdateProject();
void UpdateProjectID();
void UpdateProjectName();
void UpdateProjectDescription();
void UpdateAllProjectDetails();
void DeleteProject();
void SortProjectsByIDAsc();
void SortProjectsByIDDesc();
void SortProjectsByNameAsc();
void SortProjectsByNameDesc();
void delete_tasks_by_projectID(char projectID[5]);

// Function Prototypes User menu:
void display_user_menu();
void add_user();
void search_user();
void delete_user();
void display_users();
void update_user();
void sort_users_by_id();
int get_valid_int(char*prompt);
void sort_by_name();
void sort_user_by_rollno();
void deleteCommentsByUserID(char userID[5]);

// Function Prototypes Comment menu:
void display_commentMenu();
void addComment();
void displayComments();
void searchComment();
void updateComment();
void deleteCommentByID();
void sortByCommentID(int order);
int check_task_exists(char taskID[5]);
int check_user_exists(char userID[5]);

// Function Prototypes for file handling:
int load_tasks_from_file();
int save_tasks_to_file();
void SaveProjectsToFile();
void LoadProjectsFromFile();
void save_users_to_file();
void load_users_from_file();
void saveCommentsToFile();
void loadCommentsFromFile();

//utility functions:
void pause();
void print_centered_with_border(const char *text,int width);
void print_centered(const char *text,int width);
int check_input_validation(char member_input[100],int member);
void ClearScreen();
void PrintProjectRow(char id[5],const char* name,const char* desc);
void PrintProjectHeader();
int get_valid_int(char *prompt);

// main function :
int main()
{
system("cls");
load_tasks_from_file();
LoadProjectsFromFile();
loadCommentsFromFile();
load_users_from_file();
display_welcomeScreen();
display_mainMenu();
return 0;
}

//FUNCTION DEFINATIONS:

//function to display welcome screen:
void display_welcomeScreen()
{
system("cls");
printf("\n\n\n\n\n\n");
printf(MAGENTA_BG CYAN_BFG BOLD BLINK);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
printf(" ||                                                                                                                  || \n");
print_centered_with_border("WELCOME TO COLLABTASK HUB ",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
print_centered_with_border("------------------------------------------------------------------------------------------",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
print_centered_with_border("YOUR WORK FLOW, SIMPLIFIED AND SYNCRONIZED  ",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
loading_animation();
}

//function for main menu:
void display_mainMenu()
{
int choice;
while (1)
{
while(1)
{
system("cls");
printf("\n\n\n\n\n");
printf(BLUE_BG CYAN_BFG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
print_centered_with_border("==================================================== MAIN MENU ===================================================",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
printf(" ||1. USER MENU                                                                                                      || \n");
printf(" ||2. PROJECT MANAGEMENT                                                                                             || \n");
printf(" ||3. TASK MANAGEMENT                                                                                                || \n");
printf(" ||4. COMMENTS                                                                                                       || \n");
printf(" ||5. EXIT                                                                                                           || \n");
printf(" ||                                                                                                                  || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
int result;
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
result=scanf("%d",&choice);
if(result==1)
break;
while(getchar()!='\n');
printf(RED_FG BOLD);
print_centered("Invalid input! Press enter and please enter a number...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
}
getchar();
switch(choice)
{
case 1:
display_user_menu();
break;
case 2:
ShowProjectMenu();
break;
case 4:
display_commentMenu();
break;
case 3:
display_taskMenu();
break;
case 5:
return;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
}
}
}

//FUNCTIONS IN TASK MENU :-

//function for task menu:
void display_taskMenu()
{
int choice;
while (1)
{
while(1)
{
system("cls");
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
print_centered_with_border("=================================================== TASK MENU ====================================================",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
printf(" ||1. ADD NEW TASK                                                                                                   || \n");
printf(" ||2. VIEW TASK                                                                                                      || \n");
printf(" ||3. UPDATE TASK                                                                                                    || \n");
printf(" ||4. DELETE TASK                                                                                                    || \n");
printf(" ||5. LIST ALL TASKS                                                                                                 || \n");
printf(" ||6. BACK TO MAIN MENU                                                                                              || \n");
printf(" ||                                                                                                                  || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
int result;
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
result=scanf("%d",&choice);
if(result==1)
break;
while(getchar()!='\n');
printf(RED_FG BOLD);
print_centered("Invalid input! Press enter and please enter a number...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
}
getchar();
switch(choice)
{
case 1:
addTask();
break;
case 2:
viewTask();
break;
case 3:
updateTask();
break;
case 4:
deleteTask();
break;
case 5:
listAllTasks();
break;
case 6:
return;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
}
}
}

//function for add task submenu:
void addTask()
{
int index_itrator,i,exists=0;
char task_id[5];
add:
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("ADD NEW TASK",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
print_centered_with_border("EXISTING TASK IDs ",CONSOLE_WIDTH);
for(i=0;i<task_count;i++)
{
if(tasks[i].is_used==1)
{
print_centered_with_border(tasks[i].taskID,CONSOLE_WIDTH);
exists=1;
}
}
if(!exists)
print_centered_with_border(" NO TASK EXISTS.. ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
if(task_count>=MAX_TASKS)
{
printf(RED_FG BOLD "   Task storage limit exceeded!please free some storage to continue ....\n\n" RESET);
pause();
return;
}
while(1)
{
printf(YELLOW_FG BOLD"   Enter TaskID(e.g. T001):" RESET);
scanf("%4s",task_id);
while(getchar()!='\n');
if(check_input_validation(task_id,1))
break;
printf(RED_FG BOLD "   INVALID TASK ID... Please press enter and try again with format (T001)" RESET);
while(getchar()!='\n');
}
for(index_itrator=0;index_itrator<task_count;index_itrator++)
{
if((tasks[index_itrator].is_used==1)&&(strcmp(task_id,tasks[index_itrator].taskID)==0))
{
printf(RED_FG BOLD "   TaskID exists ! press enter and try again with another ID." RESET);
while(getchar()!='\n');
goto add;
}
}
get_task_record(task_id);
printf(MAGENTA_FG BOLD "  ====================================================================================================================  \n" RESET);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(YELLOW_FG BOLD);
print_centered("PRESS ENTER TO GO BACK TO TASK MENU...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
save_tasks_to_file();
}

// function to input attributes of task from user:
void get_task_record(char task_id[5])
{
int itrator;
int i,test_var=0;
for(itrator=0;itrator<MAX_TASKS;itrator++)
{
if(tasks[itrator].is_used==0)
{
strcpy(tasks[itrator].taskID,task_id);
while(1)
{
printf(YELLOW_FG BOLD "   Enter ProjectID(e.g. P001):" RESET);
scanf("%4s",tasks[itrator].projectID);
while(getchar()!='\n');
if(!check_input_validation(tasks[itrator].projectID,2))
{
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
continue;
}
if(!check_project_exists(tasks[itrator].projectID))
{
printf(RED_FG BOLD "   PROJECT ID does not exist! Please create the project first in Project Menu.\n" RESET);
return;
}
break;
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter Title(e.g.Task menu):" RESET);
scanf(" %[^\n]",tasks[itrator].title);
while(getchar()!='\n');
if(check_input_validation(tasks[itrator].title,3))
break;
printf(RED_FG BOLD "   INVALID TITLE... Please press enter and try again with max length 35 characters." RESET);
while(getchar()!='\n');
}
while(1)
{
printf(YELLOW_FG BOLD "   Assigned to(e.g. Eman Shafiq):" RESET);
scanf(" %[^\n]",tasks[itrator].assigned_to);
while(getchar()!='\n');
if(check_input_validation(tasks[itrator].assigned_to,4))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 20 characters." RESET);
while(getchar()!='\n');
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter status(e.g. Completed,Inprogress,Pending):" RESET);
scanf("%s",tasks[itrator].status);
while(getchar()!='\n');
if(check_input_validation(tasks[itrator].status,5))
break;
printf(RED_FG BOLD "   INVALID STATUS! Please press enter and try again..." RESET);
while(getchar()!='\n');
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter priority(e.g.High,Medium,Low):" RESET);
scanf("%s",tasks[itrator].priority);
while(getchar()!='\n');
if(check_input_validation(tasks[itrator].priority,6))
break;
printf(RED_FG BOLD "   INVALID PRIORITY ! Please press enter and try again..." RESET);
while(getchar()!='\n');
}
tasks[itrator].is_used=1;
for(i=0;i<task_count;i++)
{
if(tasks[i].is_used==0)
{
test_var=1;
break;
}
}
if(test_var==1)
return;
else
task_count++;
break;
}
}
}

// Check if project exists:
int check_project_exists(char projectID[5])
{
int i;
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectID,projectID)==0&&Projects[i].is_used)
return 1;
}
return 0;
}

//function for update task submenu:
void updateTask()
{
char task_id[5];
int i,found=0,choice;
while(1)
{
while(1)
{
system("cls");
printf("\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE TASK ",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf(" ||1. UPDATE PROJECT ID                                                                                              || \n");
printf(" ||2. UPDATE TITLE                                                                                                   || \n");
printf(" ||3. UPDATE ASSIGNED TO                                                                                             || \n");
printf(" ||4. UPDATE STATUS                                                                                                  || \n");
printf(" ||5. UPDATE PRIORITY                                                                                                || \n");
printf(" ||6. UPDATE ALL                                                                                                     || \n");
printf(" ||7. BACK TO TASK MENU                                                                                              || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
int result;
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
result=scanf("%d",&choice);
if(result==1)
break;
while(getchar()!='\n');
printf(RED_FG BOLD);
print_centered("Invalid input! Press enter and please enter a number...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
}
getchar();
if(choice==7)
return;
while(1)
{
printf(YELLOW_FG BOLD"   Enter TaskID to Update Record:" RESET);
scanf("%4s",task_id);
while(getchar()!='\n');
if(check_input_validation(task_id,1))
break;
printf(RED_FG BOLD "   INVALID TASK ID... Please press enter and try again with format (T001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<task_count;i++)
{
if(tasks[i].is_used&&strcmp(tasks[i].taskID,task_id)==0)
{
found=1;
printf(MAGENTA_FG BOLD"   CURRENT DETAILS\n" RESET);
printf(CYAN_BFG);
printf("   PROJECT ID: %s\n",tasks[i].projectID);
printf("   TITLE: %s\n",tasks[i].title);
printf("   ASSIGNED TO: %s\n",tasks[i].assigned_to);
printf("   STATUS: %s\n",tasks[i].status);
printf("   PRIORITY: %s\n",tasks[i].priority);
printf(RESET);
printf(GREEN_FG BOLD );
print_centered("UPDATING TASK....",CONSOLE_WIDTH);
printf(RESET);
printf("\n");
switch(choice)
{
case 1:
while(1)
{
printf(YELLOW_FG BOLD "   Enter ProjectID(e.g. P001):" RESET);
scanf("%4s",tasks[i].projectID);
while(getchar()!='\n');
if(!check_input_validation(tasks[i].projectID,2))
{
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
continue;
}
if(!check_project_exists(tasks[i].projectID))
{
printf(RED_FG BOLD "   PROJECT ID does not exist! Please press enter and enter an existing Project ID." RESET);
while(getchar()!='\n');
}
else
break;
}
break;
case 2:
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Title:" RESET);
scanf(" %[^\n]",tasks[i].title);
while(getchar()!='\n');
if(check_input_validation(tasks[i].title,3))
break;
printf(RED_FG BOLD "   INVALID TITLE... Please press enter and try again with max length 35 characters." RESET);
while(getchar()!='\n');
}
break;
case 3:
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Assigned Member:" RESET);
scanf(" %[^\n]",tasks[i].assigned_to);
while(getchar()!='\n');
if(check_input_validation(tasks[i].assigned_to,4))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 20 characters." RESET);
while(getchar()!='\n');
}
break;
case 4:
while(1)
{
printf(YELLOW_FG BOLD "   Enter status(e.g. Completed,Inprogress,Pending):" RESET);
scanf("%s",tasks[i].status);
while(getchar()!='\n');
if(check_input_validation(tasks[i].status,5))
break;
printf(RED_FG BOLD "   INVALID STATUS! Please press enter and try again..." RESET);
while(getchar()!='\n');
}
break;
case 5:
while(1)
{
printf(YELLOW_FG BOLD "   Enter priority(e.g.High,Medium,Low):" RESET);
scanf("%s",tasks[i].priority);
while(getchar()!='\n');
if(check_input_validation(tasks[i].priority,6))
break;
printf(RED_FG BOLD "   INVALID PRIORITY ! Please press enter and try again..." RESET);
while(getchar()!='\n');
}
break;
case 6:
while(1)
{
printf(YELLOW_FG BOLD "   Enter ProjectID(e.g. P001):" RESET);
scanf("%s",tasks[i].projectID);
while(getchar()!='\n');
if(!check_input_validation(tasks[i].projectID,2))
{
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
continue;
}
if(!check_project_exists(tasks[i].projectID))
{
printf(RED_FG BOLD "   Project ID does not exist! Please create the project first in Project Menu." RESET);
printf(YELLOW_FG BOLD "\n   Press enter to go back..." RESET);
while(getchar()!='\n');
return;
}
break;
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Title:" RESET);
scanf(" %[^\n]",tasks[i].title);
while(getchar()!='\n');
if(check_input_validation(tasks[i].title,3))
break;
printf(RED_FG BOLD "   INVALID TITLE... Please press enter and try again with max length 35 characters." RESET);
while(getchar()!='\n');
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Assigned Member:" RESET);
scanf(" %[^\n]",tasks[i].assigned_to);
while(getchar()!='\n');
if(check_input_validation(tasks[i].assigned_to,4))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 20 characters." RESET);
while(getchar()!='\n');
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter status(e.g. Completed,Inprogress,Pending):" RESET);
scanf("%s",tasks[i].status);
while(getchar()!='\n');
if(check_input_validation(tasks[i].status,5))
break;
printf(RED_FG BOLD "   INVALID STATUS! Please press enter and try again..." RESET);
while(getchar()!='\n');
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter priority(e.g.High,Medium,Low):" RESET);
scanf("%s",tasks[i].priority);
while(getchar()!='\n');
if(check_input_validation(tasks[i].priority,6))
break;
printf(RED_FG BOLD "   INVALID PRIORITY ! Please press enter and try again..." RESET);
while(getchar()!='\n');
}
break;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
}
printf("\n");
printf(GREEN_FG BOLD);
print_centered("Task updated successfully!",CONSOLE_WIDTH);
printf(RESET);
printf("\n");
break;
}
}
if(!found)
{
printf(RED_FG BOLD "\n   Task not found!\n" RESET);
pause();
return;
}
printf(MAGENTA_FG BOLD "  ====================================================================================================================  \n" RESET);
pause();
}
save_tasks_to_file();
}

//function for delete task submenu:
void deleteTask()
{
char task_id[5];
int i,j,exists=0,found=0;
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("DELETE TASK ",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
print_centered_with_border("EXISTING TASK IDs ",CONSOLE_WIDTH);
for(i=0;i<task_count;i++)
{
if(tasks[i].is_used==1)
{
print_centered_with_border(tasks[i].taskID,CONSOLE_WIDTH);
exists=1;
}
}
if(!exists)
print_centered_with_border(" NO TASK EXISTS.. ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD"   Enter TaskID to Delete Record:" RESET);
scanf("%s",task_id);
while(getchar()!='\n');
if(check_input_validation(task_id,1))
break;
printf(RED_FG BOLD "   INVALID TASK ID... Please press enter and try again with format (T001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<task_count;i++)
{
if(tasks[i].is_used&&strcmp(tasks[i].taskID,task_id)==0)
{
tasks[i].is_used=0;
// Delete all comments for this task-
delete_comments_by_taskID(task_id);
for(j=i;j<task_count-1;j++)
tasks[j]=tasks[j+1];
task_count--;
tasks[task_count].is_used=0;
found=1;
printf(GREEN_FG BOLD "\n   Task and its Comments deleted successfully!\n" RESET);
break;
}
}
if(!found)
printf(RED_FG BOLD "   Task not found!\n" RESET);
pause();
save_tasks_to_file();
}

// Delete comments by task ID:
void delete_comments_by_taskID(char taskID[5])
{
int i;
for(i=0;i<commentCount;i++)
{
if(strcmp(comments[i].taskID,taskID)==0&&comments[i].is_used)
{
comments[i].is_used=0;
}
}
// Remove deleted comments from array-
int new_index=0;
for(i=0;i<commentCount;i++)
{
if(comments[i].is_used)
{
comments[new_index++]=comments[i];
}
}
commentCount=new_index;
saveCommentsToFile();
}

//function for view task submenu:
void viewTask()
{
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("TASK DETAILS",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
find_task_record(); 
printf(MAGENTA_FG BOLD);                                      
printf("  ====================================================================================================================  \n");
printf(RESET);
printf("                                                                                                                        \n");
pause();
}

// function for finding task record by taskID:
void find_task_record()
{
int index_itrator;
char task_id[5];
printf("\n");
printf(YELLOW_FG BOLD "   ENTER TASK ID:" RESET);
scanf("%s",task_id);
while(getchar()!='\n');
for(index_itrator=0;index_itrator<task_count;index_itrator++)
{
if(strcmp(task_id,tasks[index_itrator].taskID)==0&&tasks[index_itrator].is_used==1)
{
printf(CYAN_FG BOLD );
printf("   TASK ID: %s\n",tasks[index_itrator].taskID);
printf("   PROJECT ID: %s\n",tasks[index_itrator].projectID);
printf("   TITLE: %s\n",tasks[index_itrator].title);
printf("   ASSIGNED TO: %s\n",tasks[index_itrator].assigned_to);
printf("   STATUS: %s\n",tasks[index_itrator].status);
printf("   PRIORITY: %s\n",tasks[index_itrator].priority);
printf(RESET);
return;
}
}
printf(RED_FG BOLD );
print_centered("Task not found.....\n",CONSOLE_WIDTH);
printf( RESET);
}

//function for list all tasks submenu:
void listAllTasks()
{
int i,found=0,choice,order;
char ans[3];
while(1)
{
system("cls");
printf("\n\n\n\n\n");
printf(CYAN_FG BOLD);
print_centered("TASKS LIST",CONSOLE_WIDTH);
printf("\n");
printf(RESET);
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
printf(" || %-7s | %-10s | %-35s | %-20s | %-15s | %-10s || \n","TaskID","ProjectID","Title","AssignedTo","Status","Priority");
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
for(i=0;i<task_count;i++)
{
if(tasks[i].is_used==1)
{
printf(" || %-7s | %-10s | %-35s | %-20s | %-15s | %-10s || \n",tasks[i].taskID,tasks[i].projectID,tasks[i].title,tasks[i].assigned_to,tasks[i].status,tasks[i].priority);
found=1;
}
}
if(found==0)
{
printf(" || %-112s || ", "NO TASK AVAILABLE.....");
}
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf(RESET);
if(task_count>1)
{
printf(CYAN_FG BOLD "   DO YOU WANT TO SORT TASKS (YES/NO)?" RESET);
scanf("%s",ans);
while(getchar()!='\n');
if(strcmp(ans,"YES")==0||strcmp(ans,"yes")==0||strcmp(ans,"Yes")==0)
{
printf(MAGENTA_FG BOLD"   1.SORT BY TASK ID\n"RESET);
printf(MAGENTA_FG BOLD"   2.SORT BY TITLE\n"RESET);
while(1)
{
printf(CYAN_FG BOLD "   ENTER CHOICE:" RESET);
scanf("%d",&choice);
while(getchar()!='\n');
if(choice==1||choice==2)
break;
printf(RED_FG BOLD"   INVALID CHOICE... please press enter and try again with correct choice." RESET);
while(getchar()!='\n');
}
printf(MAGENTA_FG BOLD "   1. ASCENDING\n" RESET);
printf(MAGENTA_FG BOLD "   2. DESCENDING\n" RESET);
while(1)
{
printf(CYAN_FG BOLD "   ENTER ORDER:" RESET);
scanf("%d",&order);
while(getchar()!='\n');
if(order==1||order==2)
break;
printf(RED_FG BOLD"   INVALID ORDER... please press enter and try again with correct order." RESET);
while(getchar()!='\n');
}
switch(choice)
{
case 1:
if(order==1)
sort_by_taskID(1);
if(order==2)
sort_by_taskID(2);
break;
case 2:
if(order==1)
sort_by_title(1);
if(order==2)
sort_by_title(2);
break;
}
}
else if(strcmp(ans,"NO")==0||strcmp(ans,"no")==0||strcmp(ans,"No")==0)
{
pause();
return;
}
else
{
printf(RED_FG BOLD "   INVALID... please press enter and try again with yes or no."RESET);
while(getchar()!='\n');
}
}
else
{
pause();
return;
}
}
}

// function for sorting by task id using bubble sort method:
void sort_by_taskID(int order)
{
int i,j;
Task temp;
for(i=0;i<task_count-1;i++)
{
for(j=0;j<task_count-1-i;j++)
{
if(tasks[j].is_used&&tasks[j+1].is_used)
{
if((order==1&&strcmp(tasks[j].taskID,tasks[j+1].taskID)>0)||(order==2&&strcmp(tasks[j].taskID,tasks[j+1].taskID)<0))
{
temp=tasks[j];
tasks[j]=tasks[j+1];
tasks[j+1]=temp;
}
}
}
}
}

// function for sorting by title using selection sort method:
void sort_by_title(int order)
{
int i,j,selected;
Task temp;
for(i=0;i<task_count-1;i++)
{
selected=i;
for(j=i+1;j<task_count;j++)
{
if(tasks[j].is_used&&tasks[selected].is_used)
{
if((order==1&&strcmp(tasks[j].title,tasks[selected].title)<0)||(order==2&&strcmp(tasks[j].title,tasks[selected].title)>0))
selected=j;
}
}
if(selected!=i)
{
temp=tasks[i];
tasks[i]=tasks[selected];
tasks[selected]=temp;
}
}
}

//fuction to load records from hard disk:
int load_tasks_from_file()
{
FILE* fptr=fopen(TASK_FILE,"rb");
if(fptr==NULL)
return 1;
fread(&task_count,sizeof(int),1,fptr);
fread(tasks,sizeof(Task),MAX_TASKS,fptr);
fclose(fptr);
return 0;
}

//fuction to save record:
int save_tasks_to_file()
{
FILE* fptr=fopen(TASK_FILE,"wb");
if(fptr==NULL)
return 1;
fwrite(&task_count,sizeof(int),1,fptr);
fwrite(tasks,sizeof(Task),MAX_TASKS,fptr);
fclose(fptr);
return 0;
}

//function for pause:
void pause()
{
printf("\n\n");
printf(YELLOW_FG BOLD);
print_centered("PRESS ENTER TO GO BACK ...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
}

//function for loading animation:
void loading_animation()
{
printf(YELLOW_FG BOLD);
print_centered("PRESS ENTER TO CONTINUE....",CONSOLE_WIDTH);
while(getchar()!='\n');
printf(RESET);
printf(GREEN_FG BOLD);
print_centered("LOADING...",CONSOLE_WIDTH);
printf(RESET);
printf("\n\n");
int i,m,n;
int animation_width=50;
int spacing=(CONSOLE_WIDTH-animation_width)/2;
for(i=0;i<spacing;i++) 
printf(" ");
for(m=0;m<animation_width;m++)
{
printf("%s%s",GREEN_BBG," ");
for(n=0;n<=3000000;n++) 
{
}
}
printf(RESET);
printf("\n");
}

//function for center alignment and side border:
void print_centered_with_border(const char *text,int width) 
{
int i;
int length=strlen(text);
int spaces=(width-length)/2;
if (spaces<0) 
spaces=0;
printf(" ");
printf("||");
for(i=0;i<spaces-3;i++)
{
printf(" ");
}
printf("%s",text);
for(i=0;i<spaces-3;i++)
{
printf(" ");	
}
printf("||");
printf(" ");
printf("\n");
}

//function for center alignment:
void print_centered(const char *text,int width) 
{
int i;
int length=strlen(text);
int spaces=(width-length)/2;
if (spaces<0) 
spaces=0;
for(i=0;i<spaces;i++)
{
printf(" ");
}
printf("%s",text);
}

// function for input validation :
int check_input_validation(char member_input[100],int member)
{
int i;
switch(member)
{
case 1:
{
char task_id[5];
strcpy(task_id,member_input);
if(strlen(task_id)!=4)
return 0;
if(task_id[0]!='T')
return 0;
for(i=1;i<4;i++)
{
if(task_id[i]<'0'||task_id[i]>'9')
return 0;
}
return 1;
}
case 2:
{
char project_id[5];
strcpy(project_id,member_input);
if(strlen(project_id)!=4)
return 0;
if(project_id[0]!='P')
return 0;
for(i=1;i<4;i++)
{
if(project_id[i]<'0'||project_id[i]>'9')
return 0;
}
return 1;
}
case 3:
{
char title[35];
strcpy(title,member_input);
if(strlen(title)>35)
return 0;
return 1;
}
case 4:
{
char assigned_to[20];
strcpy(assigned_to,member_input);
if(strlen(assigned_to)>20)
return 0;
return 1;
}
case 5:
{
char status[15];
strcpy(status,member_input);
char Status1[15]="Completed",status1[15]="completed",STATUS1[15]="COMPLETED";
char Status2[15]="Inprogress",status2[15]="inprogress",STATUS2[15]="INPROGRESS";
char Status3[15]="Pending",status3[15]="pending",STATUS3[15]="PENDING";
if(strcmp(status,Status1)==0||strcmp(status,status1)==0||strcmp(status,STATUS1)==0||strcmp(status,Status2)==0||strcmp(status,status2)==0||strcmp(status,STATUS2)==0||strcmp(status,Status3)==0||strcmp(status,status3)==0||strcmp(status,STATUS3)==0)
return 1;
else
return 0;
}
case 6:
{
char priority[10];
strcpy(priority,member_input);
char Priority1[10]="High",priority1[10]="high",PRIORITY1[10]="HIGH";
char Priority2[10]="Low",priority2[10]="low",PRIORITY2[10]="LOW";
char Priority3[10]="Medium",priority3[10]="medium",PRIORITY3[10]="MEDIUM";
if(strcmp(priority,Priority1)==0||strcmp(priority,priority1)==0||strcmp(priority,PRIORITY1)==0||strcmp(priority,Priority2)==0||strcmp(priority,priority2)==0||strcmp(priority,PRIORITY2)==0||strcmp(priority,Priority3)==0||strcmp(priority,priority3)==0||strcmp(priority,PRIORITY3)==0)
return 1;
else
return 0;
default :
return 0;
}
case 7:
{
char projectName[28];
strcpy(projectName,member_input);
if(strlen(projectName)>28)
return 0;
return 1;
}
case 8:
{
char description[75];
strcpy(description,member_input);
if(strlen(description)>75)
return 0;
return 1;
}
case 9:
{
char userID[5];
strcpy(userID,member_input);
if(strlen(userID)!=4)
return 0;
if(userID[0]!='U')
return 0;
for(i=1;i<4;i++)
{
if(userID[i]<'0'||userID[i]>'9')
return 0;
}
return 1;
}
case 10:
{
char commentID[5];
strcpy(commentID,member_input);
if(strlen(commentID)!=4)
return 0;
if(commentID[0]!='C')
return 0;
for(i=1;i<4;i++)
{
if(commentID[i]<'0'||commentID[i]>'9')
return 0;
}
return 1;
}
case 11:
{
char comment[87];
strcpy(comment,member_input);
if(strlen(comment)>87)
return 0;
return 1;
}
}
}

// FUNCTIONS IN PROJECT MENU:-

// PROJECT MENU Function Definition:
void ShowProjectMenu() 
{
int choice;
while(1) 
{
while(1)
{
ClearScreen();
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
print_centered_with_border("================================================== PROJECT MENU ==================================================",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
printf(" ||1. ADD NEW PROJECT                                                                                                || \n");
printf(" ||2. SEARCH PROJECT                                                                                                 || \n");
printf(" ||3. UPDATE PROJECT                                                                                                 || \n");
printf(" ||4. DELETE PROJECT                                                                                                 || \n");
printf(" ||5. LIST ALL PROJECTS                                                                                              || \n");
printf(" ||6. BACK TO MAIN MENU                                                                                              || \n");
printf(" ||                                                                                                                  || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
int result;
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
result=scanf("%d",&choice);
if(result==1)
break;
while(getchar()!='\n');
printf(RED_FG BOLD);
print_centered("Invalid input! Press enter and please enter a number...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
}
getchar();
switch(choice) 
{
case 1:
AddProject();
save_tasks_to_file();
break;
case 2:
SearchProject();
break;
case 3:
UpdateProject();
save_tasks_to_file();
break;
case 4:
DeleteProject();
save_tasks_to_file();
break;
case 5:
DisplayProjects();
break;
case 6:
return;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
}
}
}

//Opening New screen Function Definition:
void ClearScreen()
{
system("cls"); 
}

// Add Project function definition:
void AddProject()
{
ClearScreen();
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("ADD NEW PROJECT ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
if (ProjectCount>=MAX_PROJECTS)
{
printf(RED_FG BOLD "\n   Project list is already full!\n" RESET);
pause();
return;
}
char project_id[5];
while(1)
{
printf(YELLOW_FG BOLD "   Enter ProjectID(e.g. P001):" RESET);
scanf("%4s",project_id);
while(getchar()!='\n');
if(check_input_validation(project_id,2))
break;
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
}
int i;
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectID,project_id)==0&&Projects[i].is_used)
{
printf(RED_FG BOLD "\n   Project already exists with this ID!\n" RESET);
pause();
return;
}
}
strcpy(Projects[ProjectCount].ProjectID,project_id);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project Name: " RESET);
scanf(" %[^\n]",Projects[ProjectCount].ProjectName);
while(getchar()!='\n');
if(check_input_validation(Projects[ProjectCount].ProjectName,7))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 20 characters." RESET);
while(getchar()!='\n');
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project Description: " RESET);
scanf(" %[^\n]",Projects[ProjectCount].ProjectDescription);
while(getchar()!='\n');
if(check_input_validation(Projects[ProjectCount].ProjectDescription,8))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 70 characters." RESET);
while(getchar()!='\n');
}
Projects[ProjectCount].is_used=1;
ProjectCount++;
printf(GREEN_FG BOLD "\n   Project Successfully added!\n" RESET);
SaveProjectsToFile();
pause();
}

// Printing table header function definition:
void PrintProjectHeader() 
{
printf(" ||%-9s|%-28s|%-75s|| \n","ProjectID","Project Name","Description");
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
}

// Printing a single project row:
void PrintProjectRow(char id[5],const char* name,const char* desc) 
{
printf(" ||%-9s|%-28s|%-75s|| \n",id,name,desc);
}

// Displaying projects function definition:
void DisplayProjects() 
{
int choice;
int i;
if(ProjectCount==0) 
{
ClearScreen();
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("NO PROJECTS TO DISPLAY",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
pause();
return;
}
while(1) 
{
ClearScreen();
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("DISPLAY PROJECTS",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf(" ||1. UNSORTED                                                                                                       || \n");
printf(" ||2. SORT BY ID ASCENDING                                                                                           || \n");
printf(" ||3. SORT BY ID DESCENDING                                                                                          || \n");
printf(" ||4. SORT BY NAME A-Z                                                                                               || \n");
printf(" ||5. SORT BY NAME Z-A                                                                                               || \n");
printf(" ||6. BACK TO PROJECT MENU                                                                                           || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
scanf("%d",&choice);
while(getchar()!='\n');
switch(choice) 
{
case 1:
// keep unsorted
break; 
case 2:
SortProjectsByIDAsc();
break;
case 3:
SortProjectsByIDDesc();
break;
case 4:
SortProjectsByNameAsc();
break;
case 5:
SortProjectsByNameDesc();
break;
case 6:
return;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
continue;
}
ClearScreen();
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("ALL PROJECTS",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
PrintProjectHeader();
for(i=0;i<ProjectCount;i++) 
{
if(Projects[i].is_used)
PrintProjectRow(Projects[i].ProjectID,Projects[i].ProjectName,Projects[i].ProjectDescription);
}
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
pause();
}
}						

// Sort by Project ID Ascending function definition:
void SortProjectsByIDAsc() 
{
int i,j;
Project temp;
for(i=0;i<ProjectCount-1;i++) 
{
for(j=0;j<ProjectCount-i-1;j++)
{
if(strcmp(Projects[j].ProjectID,Projects[j+1].ProjectID)>0&&Projects[j].is_used&&Projects[j+1].is_used) 
{
temp=Projects[j];
Projects[j]=Projects[j+1];
Projects[j+1]=temp;
}
}
}
}

// Sort by Project ID Descending function definition:
void SortProjectsByIDDesc() 
{
int i,j;
Project temp;
for(i=0;i<ProjectCount-1;i++) 
{
for(j=0;j<ProjectCount-i-1;j++)
{
if(strcmp(Projects[j].ProjectID,Projects[j+1].ProjectID)<0&&Projects[j].is_used&&Projects[j+1].is_used) 
{
temp=Projects[j];
Projects[j]=Projects[j+1];
Projects[j+1]=temp;
}
}
}
}

// Sort by Project Name A-Z function definition:
void SortProjectsByNameAsc() 
{
int i,j;
Project temp;
for(i=0;i<ProjectCount-1;i++) 
{
for(j=0;j<ProjectCount-i-1;j++) 
{
if(strcmp(Projects[j].ProjectName,Projects[j+1].ProjectName)>0&&Projects[j].is_used&&Projects[j+1].is_used) 
{
temp=Projects[j];
Projects[j]=Projects[j+1];
Projects[j+1]=temp;
}
}
}
}

// Sort by Project Name Z-A function definition:
void SortProjectsByNameDesc() 
{
int i,j;
Project temp;
for(i=0;i<ProjectCount-1;i++) 
{
for(j=0;j<ProjectCount-i-1;j++) 
{
if(strcmp(Projects[j].ProjectName,Projects[j+1].ProjectName)<0&&Projects[j].is_used&&Projects[j+1].is_used) 
{
temp=Projects[j];
Projects[j]=Projects[j+1];
Projects[j+1]=temp;
}
}
}
}

// Searching Function Definition with:
void SearchProject()
{
int ch;
while (1) 
{
ClearScreen();
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("SEARCH PROJECT",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf(" ||1. SEARCH PROJECT BY ID                                                                                           || \n");
printf(" ||2. SEARCH PROJECT BY NAME                                                                                         || \n");
printf(" ||3. BACK TO PROJECT MENU                                                                                           || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
scanf("%d",&ch);
while(getchar()!='\n');
switch(ch) 
{
case 1:
SearchProjectByID();
break;
case 2:
SearchProjectByName();
break;
case 3:
return;
break;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
}
}
}	

// Searching by ID function Definition:          				
void SearchProjectByID()
{
ClearScreen();
int i;
char id[5];
printf("\n\n\n\n\n");
printf(CYAN_BBG LIGHT_PINK_BFG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("SEARCH PROJECT BY ID",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project ID: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
if(check_input_validation(id,2))
break;
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectID,id)==0&&Projects[i].is_used)
{
ClearScreen();
printf("\n\n\n\n\n");
printf(GREEN_BBG YELLOW_FG BOLD);
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("PROJECT FOUND ",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(CYAN_FG BOLD"\n   PROJECT ID:" WHITE_FG" %s\n",Projects[i].ProjectID);
printf(CYAN_FG BOLD"   PROJECT NAME:" WHITE_FG" %s\n",Projects[i].ProjectName);
printf(CYAN_FG BOLD"   DESCRIPTION:" WHITE_FG" %-75s\n" RESET,Projects[i].ProjectDescription);
printf(YELLOW_FG BOLD" ====================================================================================================================== \n" RESET);
pause();
return;
}
}
printf(RED_FG BOLD "\n   No Project found with this ID!\n" RESET);
pause();
}

// Searching by name function Definition: 						 
void SearchProjectByName()
{
ClearScreen();
char name[50];
int i,found=0;
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("SEARCH PROJECT BY NAME",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(YELLOW_FG BOLD "   Enter Project Name: " RESET);
scanf(" %[^\n]",name);
while(getchar()!='\n');
ClearScreen();
printf("\n\n\n\n\n");
printf(GREEN_BBG YELLOW_FG BOLD);
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("SEARCH RESULTS",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf("                                                                                                                        \n");
printf(RESET);
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectName,name)==0&&Projects[i].is_used)
{
found=1;
printf(CYAN_FG BOLD"   PROJECT ID: %s\n",Projects[i].ProjectID);
printf("   PROJECT NAME: %s\n",Projects[i].ProjectName);
printf("   DESCRIPTION: %-75s\n" RESET,Projects[i].ProjectDescription);
}
}
if(!found)
{
printf(RED_FG"\n   No Project found with this Name!\n" RESET);
}
printf(YELLOW_FG BOLD" ====================================================================================================================== \n" RESET);
printf(RESET);
pause();
}

// Updating Function Definition:
void UpdateProject()
{
int ch;
while(1) 
{
ClearScreen();
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE PROJECT",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf(" ||1. UPDATE PROJECT ID                                                                                              || \n");
printf(" ||2. UPDATE PROJECT NAME                                                                                            || \n");
printf(" ||3. UPDATE PROJECT DESCRIPTION                                                                                     || \n");
printf(" ||4. UPDATE ALL PROJECT DETAILS                                                                                     || \n");
printf(" ||5. BACK TO PROJECT MENU                                                                                           || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
scanf("%d",&ch);
while(getchar()!='\n');
switch(ch) 
{
case 1:
UpdateProjectID();
break;
case 2:
UpdateProjectName();
break;
case 3:
UpdateProjectDescription();
break;
case 4:
UpdateAllProjectDetails();
break;
case 5:
return;
break;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
} 
}
} 				

// Updating project ID function Definition:		
void UpdateProjectID()
{
char id[5];
char NewID[5]={0};
int i,j;
ClearScreen();
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE PROJECT ID ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project ID to update: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
if(check_input_validation(id,2))
break;
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectID,id)==0&&Projects[i].is_used)
{
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Project ID: " RESET);
scanf("%4s",NewID);
while(getchar()!='\n');
if(!check_input_validation(NewID,2))
{
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
continue;
}
for(j=0;j<ProjectCount;j++)
{
if(strcmp(Projects[j].ProjectID,NewID)==0&&Projects[j].is_used&&(j!=i))
{
printf(RED_FG BOLD "   This ID Already Exists!\n" RESET);
pause();
return;
}
}
break;
}
strcpy(Projects[i].ProjectID,NewID);
// Update all tasks with old project ID
for(j=0;j<task_count;j++)
{
if(strcmp(tasks[j].projectID,id)==0&&tasks[j].is_used)
{
strcpy(tasks[j].projectID,NewID);
}
}
save_tasks_to_file();
SaveProjectsToFile();
printf(GREEN_FG BOLD "\n   Project ID updated successfully!\n" RESET);
pause();
return;
}
}
printf(RED_FG BOLD "\n   No Project found with this ID!\n" RESET);
pause();
}           		

// Update Project Name Function defination:
void UpdateProjectName()
{
int i;
char id[5];
char NewName[50];
ClearScreen();
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE PROJECT NAME ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project ID to update name: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
if(check_input_validation(id,2))
break;
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectID,id)==0&&Projects[i].is_used)
{
printf(CYAN_FG BOLD "   Current Project Name: %s\n" RESET,Projects[i].ProjectName);
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Project Name: " RESET);
scanf(" %[^\n]",NewName);
while(getchar()!='\n');
if(check_input_validation(NewName,7))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 20 characters." RESET);
while(getchar()!='\n');
}
strcpy(Projects[i].ProjectName,NewName);
SaveProjectsToFile();
printf(GREEN_FG BOLD "\n   Project Name updated successfully!\n" RESET);
pause();
return;
}
}
printf(RED_FG BOLD "\n   No Project found with this ID!\n" RESET);
pause();
}

// Update Project Description Function defination:
void UpdateProjectDescription()
{
int i;
char id[5];
char NewDescription[100];
ClearScreen();
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE PROJECT DESCRIPTION",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project ID to update description: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
if(check_input_validation(id,2))
break;
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectID,id)==0&&Projects[i].is_used)
{
printf(CYAN_FG BOLD "   Current Description: %-75s\n" RESET,Projects[i].ProjectDescription);
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Project Description: " RESET);
scanf(" %[^\n]",NewDescription);
while(getchar()!='\n');
if(check_input_validation(NewDescription,8))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 70 characters." RESET);
while(getchar()!='\n');
}
strcpy(Projects[i].ProjectDescription,NewDescription);
SaveProjectsToFile();
printf(GREEN_FG BOLD "\n   Project Description updated successfully!\n" RESET);
pause();
return;
}
}
printf(RED_FG BOLD "\n   No Project found with this ID!\n" RESET);
pause();
}

// Update All Project Details Function defination:
void UpdateAllProjectDetails()
{
int i,j;
char id[5];
char NewID[5];
char NewName[50];
char NewDescription[100];
ClearScreen();
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE ALL PROJECT DETAILS",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project ID: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
if(check_input_validation(id,2))
break;
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<ProjectCount;i++)
{
if(strcmp(Projects[i].ProjectID,id)==0&&Projects[i].is_used)
{
printf(CYAN_FG BOLD "   Current Project ID: %s\n" RESET,Projects[i].ProjectID);
printf(CYAN_FG BOLD "   Current Project Name: %s\n" RESET,Projects[i].ProjectName);
printf(CYAN_FG BOLD "   Current Description: %-75s\n\n" RESET,Projects[i].ProjectDescription);
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Project ID: " RESET);
scanf("%4s",NewID);
while(getchar()!='\n');
if(!check_input_validation(NewID,2))
{
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
continue;
}
for(j=0;j<ProjectCount;j++)
{
if(strcmp(Projects[j].ProjectID,NewID)==0&&Projects[j].is_used&&(j!=i))
{
printf(RED_FG BOLD "   This ID Already Exists!\n" RESET);
pause();
return;
}
}
break;
}
strcpy(Projects[i].ProjectID,NewID);
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Project Name: " RESET);
scanf(" %[^\n]",NewName);
while(getchar()!='\n');
if(check_input_validation(NewName,7))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 20 characters." RESET);
while(getchar()!='\n');
}
strcpy(Projects[i].ProjectName,NewName);
while(1)
{
printf(YELLOW_FG BOLD "   Enter New Project Description: " RESET);
scanf(" %[^\n]",NewDescription);
while(getchar()!='\n');
if(check_input_validation(NewDescription,8))
break;
printf(RED_FG BOLD "   INVALID... Please press enter and try again with max length 70 characters." RESET);
while(getchar()!='\n');
}
strcpy(Projects[i].ProjectDescription,NewDescription);
// Update all tasks with old project ID
for(j=0;j<task_count;j++)
{
if(strcmp(tasks[j].projectID,id)==0&&tasks[j].is_used)
{
strcpy(tasks[j].projectID,NewID);
}
}
save_tasks_to_file();
SaveProjectsToFile();
printf(GREEN_FG BOLD "\n   All project details updated successfully!\n" RESET);
pause();
return;
}
}
printf(RED_FG BOLD "\n   No Project found with this ID!\n" RESET);
pause();
}

// Delete Project Function defination:
void DeleteProject() 
{
ClearScreen();
char id[5];
int i,j;
int found=0;
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("DELETE PROJECT",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Project ID to delete: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
if(check_input_validation(id,2))
break;
printf(RED_FG BOLD "   INVALID PROJECT ID... Please press enter and try again with format (P001)" RESET);
while(getchar()!='\n');
}
for(i=0;i<ProjectCount;i++) 
{
if(strcmp(Projects[i].ProjectID,id)==0&&Projects[i].is_used) 
{
found=1;
printf(MAGENTA_FG BOLD "\n   Are you sure you want to delete Project '%s'? (y/n): " RESET,Projects[i].ProjectName);
char confirm;
scanf(" %c",&confirm);
while(getchar()!='\n');
if(confirm=='y'||confirm=='Y') 
{
// Delete all tasks and comments for this project
delete_tasks_by_projectID(id);
// Mark project as deleted
Projects[i].is_used=0;
for(j=i;j<ProjectCount-1;j++)
Projects[j]=Projects[j+1];
ProjectCount--;
Projects[ProjectCount].is_used=0;
printf(GREEN_FG BOLD "\n   Project and all associated tasks/comments deleted successfully!\n" RESET);
SaveProjectsToFile();
} 
else 
{
printf(RED_FG BOLD"\n   Deletion cancelled.\n"RESET);
}
pause();
return;
}
}
if(!found) 
{
printf(RED_FG BOLD "\n   No Project found with this ID!\n" RESET);
pause();
}
}

// Delete tasks by project ID:
void delete_tasks_by_projectID(char projectID[5])
{
int i,j;
for(i=0;i<task_count;i++)
{
if(strcmp(tasks[i].projectID,projectID)==0&&tasks[i].is_used)
{
// Delete all comments for this task-
delete_comments_by_taskID(tasks[i].taskID);
tasks[i].is_used=0;
}
}
// Remove deleted tasks from array-
int new_index=0;
for(i=0;i<task_count;i++)
{
if(tasks[i].is_used)
{
tasks[new_index++]=tasks[i];
}
}
task_count=new_index;
save_tasks_to_file();
}

// Loading from file function definition:
void LoadProjectsFromFile()
{
FILE *handle=fopen("Projects.bin","rb");
if(handle==NULL)
{
return;
}
ProjectCount=0;
while(fread(&Projects[ProjectCount],sizeof(Project),1,handle)==1)
{
ProjectCount++;
}
fclose(handle);	
}

// Storing data permanently to file:
void SaveProjectsToFile()
{
FILE *handle=fopen("Projects.bin","wb");
if (handle==NULL) 
{
printf("Error in opening File\n");
Sleep(1000);
return;
}
int i;
for(i=0;i<ProjectCount;i++)
{
fwrite(&Projects[i], sizeof(Project),1,handle);
}
fclose(handle);	
}

//FUNCTIONS IN USER MENU:-

// User Menu:
void display_user_menu()
{
int choice;
while(1)
{
while(1)
{
system("cls");
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
print_centered_with_border("================================================== USER MENU ===================================================",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
printf(" ||1. ADD USER                                                                                                       || \n");
printf(" ||2. DISPLAY USERS                                                                                                  || \n");
printf(" ||3. SEARCH USER                                                                                                    || \n");
printf(" ||4. DELETE USER                                                                                                    || \n");
printf(" ||5. UPDATE USER                                                                                                    || \n");
printf(" ||6. SORT USERS BY ID                                                                                               || \n");
printf(" ||7. SORT USERS BY NAME                                                                                             || \n");
printf(" ||8. SORT USERS BY ROLLNO                                                                                           || \n");
printf(" ||9. BACK TO MAIN MENU                                                                                              || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
int result;
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
result=scanf("%d",&choice);
if(result==1)
break;
while(getchar()!='\n');
printf(RED_FG BOLD);
print_centered("Invalid input! Press enter and please enter a number...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
}
getchar();
switch(choice)
{
case 1: 
add_user(); 
break;
case 2: 
display_users(); 
break;
case 3: 
search_user(); 
break;
case 4: 
delete_user(); 
break;
case 5: 
update_user(); 
break;
case 6: 
sort_users_by_id(); 
break;
case 7: 
sort_by_name();
break;
case 8:
sort_user_by_rollno();
break;
case 9:
return;
default:
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
}
}
}

// Add New User:
void add_user()
{
struct user new_user;
int i,j;
if(user_count>=MAX_USERS)
{
printf(RED_FG BOLD "\n   User limit exceeded! Cannot add more users.\n" RESET);
pause();
return;
}
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("ADD NEW USER",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD"   Enter User ID (e.g.U001): " RESET);
scanf("%4s",new_user.id);
while(getchar()!='\n');
if(check_input_validation(new_user.id,9))
break;
printf(RED_FG BOLD"   INVALID USER ID... please press enter and  try again with format U001." RESET);
while(getchar()!='\n');
}
for(i=0;i<user_count;i++)
{
if(strcmp(users[i].id,new_user.id)==0&&users[i].is_used)
{
printf(RED_FG BOLD "\n  User ID already exists!\n" RESET);
pause();
return;
}
}
printf(YELLOW_FG BOLD "   Enter User Name: " RESET);
fgets(new_user.name,30,stdin);
new_user.name[strcspn(new_user.name, "\n")]='\0';
while(1)
{
int exists=0;
printf(YELLOW_FG BOLD);
new_user.roll_no=get_valid_int("   Enter Roll No: ");
printf(RESET);
for(j=0;j<user_count;j++)
{
if(users[j].roll_no==new_user.roll_no&&users[j].is_used)
{
exists=1;
break;
}
}
if(exists==1)
printf(RED_FG BOLD "   ROLL NO EXISTS... enter another roll no.\n" RESET);
if(exists==0)
break;
}
printf(YELLOW_FG BOLD "   Enter User Email: " RESET);
fgets(new_user.email,56,stdin);
new_user.email[strcspn(new_user.email,"\n")]='\0';
new_user.is_used=1;
users[user_count]=new_user;
user_count++;
save_users_to_file();
printf(GREEN_FG BOLD "\n   User added successfully.\n" RESET);
pause();
}

// Display All Users:
void display_users()
{
int i;
if(user_count==0)
{
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("NO USERS TO DISPLAY ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
pause();
return;
}
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("ALL USERS ",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf(" || %-7s | %-30s | %-10s | %-56s || \n","USER ID","NAME","ROLL NO","EMAIL");
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
for(i=0;i<user_count;i++)
{
if(users[i].is_used)
{
printf(" || %-7s | %-30s | %-10d | %-56s || \n",users[i].id,users[i].name,users[i].roll_no,users[i].email);
}
}
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
pause();
}

// Search User by Roll No:
void search_user()
{
int i,found=0;
char user_id[5];
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("SEARCH USER ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(YELLOW_FG BOLD"   Enter User ID to search: "RESET);
scanf("%4s",user_id);
while(getchar()!='\n');
for(i=0;i<user_count;i++)
{
if(strcmp(users[i].id,user_id)==0&&users[i].is_used)
{
system("cls");
printf("\n\n\n\n\n");
printf(GREEN_BBG YELLOW_FG BOLD);
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("USER FOUND",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(CYAN_FG BOLD);
printf("\n   USER ID: %4s\n",users[i].id);
printf("   NAME: %s\n",users[i].name);
printf("   ROLL NO: %d\n",users[i].roll_no);
printf("   EMAIL: %s\n",users[i].email);
printf(RESET);
printf(YELLOW_FG BOLD" ====================================================================================================================== \n" RESET);
found = 1;
pause();
return;
}
}
if(!found)
{
printf(RED_FG BOLD "\n   User not found!\n" RESET);
pause();
}
}

//  Delete User:
void delete_user()
{
int i,j,found=0;
char user_id[5];
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("DELETE USER ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(YELLOW_FG BOLD"   Enter User ID: "RESET);
scanf("%4s",user_id);
while(getchar()!='\n');
for(i=0;i<user_count;i++)
{
if(strcmp(users[i].id,user_id)==0&&users[i].is_used)
{
found=1;
// Delete all comments by this user
deleteCommentsByUserID(user_id);
users[i].is_used=0;
for(j=i;j<user_count-1;j++)
users[j]=users[j+1];
user_count--;
users[user_count].is_used=0;
save_users_to_file();
printf(GREEN_FG BOLD "\n   User and their comments deleted successfully!\n" RESET);
pause();
return;
}
}
if(!found)
{
printf(RED_FG BOLD "\n   User not found!\n" RESET);
pause();
}
}

// function to delete comments by user:
void deleteCommentsByUserID(char userID[5]) 
{
int i,index=0;
for(i=0;i<commentCount;i++)
{
if(strcmp(comments[i].userID,userID)==0&&comments[i].is_used)
{
comments[i].is_used=0;
}
}
for(i=0;i<commentCount;i++)
{
if(comments[i].is_used)
{
comments[index++]=comments[i];
}
}
commentCount=index;
saveCommentsToFile();
}

//  Update User Record:
void update_user()
{
int i,j,roll_no,found=0;
char id[5];
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE USER ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(YELLOW_FG BOLD"   Enter User ID: "RESET);
scanf("%4s",id);
while(getchar()!='\n');
for(i=0;i<user_count;i++)
{
if(strcmp(users[i].id,id)==0&&users[i].is_used)
{
found=1;
printf(CYAN_FG BOLD "   Current Name: %s\n" RESET,users[i].name);
printf(YELLOW_FG BOLD "   Enter New Name: " RESET);
fgets(users[i].name,30,stdin);
users[i].name[strcspn(users[i].name,"\n")]='\0';
printf(CYAN_FG BOLD "   Current Roll No: %d\n" RESET,users[i].roll_no);
while(1)
{
int exists=0;
printf(YELLOW_FG BOLD);
roll_no=get_valid_int("   Enter New Roll No: ");
printf(RESET);
for(j=0;j<user_count;j++)
{
if(users[j].roll_no==roll_no&&users[j].is_used)
{
exists=1;
break;
}
}
if(exists==1)
printf(RED_FG BOLD "   ROLL NO EXISTS... enter another roll no.\n" RESET);
if(exists==0)
{
users[i].roll_no=roll_no;
break;
}
}
printf(CYAN_FG BOLD "   Current Email: %s\n" RESET,users[i].email);
printf(YELLOW_FG BOLD "   Enter new Email: " RESET);
fgets(users[i].email,56,stdin);
users[i].email[strcspn(users[i].email,"\n")]='\0';
save_users_to_file();
printf(GREEN_FG BOLD "\n   User updated successfully!\n" RESET);
pause();
return;
}
}
if(!found)
{
printf(RED_FG BOLD "\n   User not found!\n" RESET);
pause();
}
}

//  Sort Users by ID:
void sort_users_by_id()
{
int i,j;
struct user temp;
if(user_count<=1)
{
printf(RED_FG BOLD "\n   Not enough users to sort.\n" RESET);
pause();
return;
}
for(i=0;i<user_count-1;i++)
{
for(j=0;j<user_count-i-1;j++)
{
if(strcmp(users[j].id,users[j+1].id)>0&&users[j].is_used&&users[j+1].is_used)
{
temp=users[j];
users[j]=users[j+1];
users[j+1]=temp;
}
}
}
printf(GREEN_FG BOLD "\n   Users sorted by ID successfully!\n" RESET);
pause();
}

// SORT BY NAME OF USER:
void sort_by_name()
{

if(user_count<=1)
{
printf(RED_FG BOLD"   Not enough users to sort.\n" RESET);
pause();
return;
}	
int i,j;
struct user temp;
for(i=0;i<user_count-1;i++)
{
for(j=0;j<user_count-i-1;j++)
{
if(strcmp(users[j].name,users[j+1].name)>0)
{
temp=users[j];
users[j]=users[j+1];
users[j+1]=temp;
}
}
}
printf(GREEN_FG BOLD"   User is sorted by name in accending order\n"RESET);
pause();
}

// SORT BY ROLL NO OF USER:
void sort_user_by_rollno()
{
int i,j;
struct user temp;
if(user_count<=1)
{
printf(RED_FG BOLD"   Not enough users to sort.\n"RESET);
pause();
return;
}
for(i=0;i<user_count-1;i++)
{
for(j=0;j<user_count-i-1;j++)
{
if(users[j].roll_no>users[j+1].roll_no)
{
temp=users[j];
users[j]=users[j+1];
users[j+1]=temp;
}
}
}
printf(GREEN_FG BOLD"   Users sorted by ID successfully!\n"RESET);
pause();
}

//  Integer Validation:
int get_valid_int(char *prompt)
{
char input[10];
int value;
while(1)
{
printf(YELLOW_FG BOLD"%s"RESET,prompt);
fgets(input,10,stdin);
if(sscanf(input,"%d",&value)==1&&strspn(input,"0123456789\n")==strlen(input))
return value;
else
printf(RED_FG"   invalid input.. only integers are allowed\n");
}
}

// File Handling:
void save_users_to_file()
{
FILE *file=fopen("userdata.bin","wb");
if(file==NULL) 
return;
fwrite(&user_count,sizeof(int),1,file);
fwrite(users,sizeof(struct user),user_count,file);
fclose(file);
}

void load_users_from_file()
{
FILE *file=fopen("userdata.bin","rb");
if(file==NULL) 
return;
fread(&user_count,sizeof(int),1,file);
fread(users,sizeof(struct user),user_count,file);
fclose(file);
}

//FUNCTIONS IN COMMENT MENU:-

// function for comment menu:
void display_commentMenu() 
{
int choice;
while(1) 
{
while(1)
{
system("cls");
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
print_centered_with_border("=================================================== COMMENT MENU =================================================",CONSOLE_WIDTH);
printf(" ||                                                                                                                  || \n");
printf(" ||1. ADD COMMENT                                                                                                    || \n");
printf(" ||2. DISPLAY COMMENTS                                                                                               || \n");
printf(" ||3. SEARCH COMMENT                                                                                                 || \n");
printf(" ||4. UPDATE COMMENT                                                                                                 || \n");
printf(" ||5. DELETE COMMENT                                                                                                 || \n");
printf(" ||6. BACK TO MAIN MENU                                                                                              || \n");
printf(" ||                                                                                                                  || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
int result;
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
result=scanf("%d",&choice);
if(result==1)
break;
while(getchar()!='\n');
printf(RED_FG BOLD);
print_centered("Invalid input! Press enter and please enter a number...",CONSOLE_WIDTH);
printf(RESET);
while(getchar()!='\n');
}
getchar();
switch (choice) 
{
case 1: 
addComment();
saveCommentsToFile();
break;
case 2: 
displayComments(); 
break;
case 3: 
searchComment(); 
break;
case 4: 
updateComment(); 
saveCommentsToFile();
break;
case 5: 
deleteCommentByID(); 
saveCommentsToFile();
break; 
case 6: 
return;
default: 
printf(RED_FG BOLD "\n   Invalid choice! Please press enter and try again ...." RESET);
while(getchar()!='\n');
}
}
}

// function to add a new comment:
void addComment() 
{
struct Comment c;
char commentID[5];
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("ADD NEW COMMENT ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Comment ID(e.g C001): " RESET);
scanf("%4s",commentID);
while(getchar()!='\n');
if(!check_input_validation(commentID,10))
{
printf(RED_FG BOLD"   INVALID COMMENT ID... please press enter and try again with format(C001)"RESET);
while(getchar()!='\n');
continue;
}
break;
}
int i;
for(i=0;i<commentCount;i++)
{
if(strcmp(comments[i].commentID,commentID)==0&&c.is_used)
{
printf(RED_FG BOLD"   COMMENT ID EXISTS..."RESET);
pause();
return;
}
}
strcpy(c.commentID,commentID);
while(1)
{
printf(YELLOW_FG BOLD "   Enter Task ID (e.g. T001): " RESET);
scanf("%4s",c.taskID);
while(getchar()!='\n');
if(!check_input_validation(c.taskID,1))
{
printf(RED_FG BOLD "   INVALID TASK ID... Please press enter and try again with format (T001)" RESET);
while(getchar()!='\n');
continue;
}
if(!check_task_exists(c.taskID)) 
{
printf(RED_FG BOLD "   TASK ID does not exist! Please create the task first in Task Menu." RESET);
printf(YELLOW_FG BOLD "\n   Press enter to go back..." RESET);
while(getchar()!='\n');
return;
}
break;
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter User ID (e.g.U001): " RESET);
scanf("%4s",c.userID);
while(getchar()!='\n');
if(!check_user_exists(c.userID)) 
{
printf(RED_FG BOLD "   USER ID does not exist! Please enter the user first in User Menu." RESET);
printf(YELLOW_FG BOLD "\n   Press enter to go back..." RESET);
while(getchar()!='\n');
return;
}
break;
}
while(1)
{
printf(YELLOW_FG BOLD "   Enter Comment Text: " RESET);
scanf(" %[^\n]",c.commentText);
if(!check_input_validation(c.commentText,11))
{
while(getchar()!='\n');
printf(RED_FG BOLD"   YOUR COMMENT IS TOO LONG... please press enter and try again with max 70 characters.");
while(getchar()!='\n');
continue;
}
break;
}
while(getchar()!='\n');
c.is_used=1;
comments[commentCount++] = c;
saveCommentsToFile();
printf(GREEN_FG BOLD "\n   Comment added successfully!\n" RESET);
pause();
}

// comments will be displayed with sorting:
void displayComments() 
{
if(commentCount==0)
{
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("NO COMMENTS TO DISPLAY  ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
pause();
return;
}
int choice,i,j;
while(1)
{
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("DISPLAY OPTIONS ",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf(" ||1. UNSORTED                                                                                                       || \n");
printf(" ||2. SORT BY COMMENT ID ASCENDING                                                                                   || \n");
printf(" ||3. SORT BY COMMENT ID DESCENDING                                                                                  || \n");
printf(" ||4. BACK TO COMMENT MENU                                                                                           || \n");
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf("\n\n");
printf(CYAN_FG BOLD);
print_centered("Enter choice: ",CONSOLE_WIDTH);
printf(RESET);
if(scanf("%d",&choice))
break;
while(getchar()!='\n');
printf(RED_FG BOLD "   INVALID CHOICE....please press enter and enter correct choice."RESET);
while(getchar()!='\n');
}
while(getchar()!='\n');
if (choice==2) 
sortByCommentID(2);
else if(choice==3) 
{
sortByCommentID(3);
}
else if(choice==4)
return;
system("cls");
printf("\n\n\n\n\n");
printf(CYAN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("ALL COMMENTS",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf(" ||%-10s|%-7s|%-7s|%-87s|| \n","COMMENT ID","TASK ID","USER ID","COMMENT");
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
for(i=0;i<commentCount;i++)
{
if(comments[i].is_used)
{
printf(" ||%-10s|%-7s|%-7s|%-87s|| \n",comments[i].commentID,comments[i].taskID,comments[i].userID,comments[i].commentText);
}
}
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
pause();
}

// function to search comment:
void searchComment() 
{
int i,found=0;
char id[5];
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("SEARCH COMMENT  ",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(YELLOW_FG BOLD "   Enter Comment ID to search: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
for(i=0;i<commentCount;i++)
{
if(strcmp(comments[i].commentID,id)==0&&comments[i].is_used)
{
found=1;
system("cls");
printf("\n\n\n\n\n");
printf(GREEN_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("COMMENT FOUND ",CONSOLE_WIDTH);
printf(" ||------------------------------------------------------------------------------------------------------------------|| \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(CYAN_FG BOLD"   COMMENT ID: %4s\n",comments[i].commentID);
printf("   TASK ID: %4s\n",comments[i].taskID);
printf("   USER ID: %4s\n",comments[i].userID);
printf("   COMMENT: %-87s\n"RESET,comments[i].commentText);
printf(YELLOW_FG BOLD" ====================================================================================================================== \n" RESET);
pause();
return;
}
}
if(!found)
{
printf(RED_FG BOLD "\n   Comment not found!\n" RESET);
pause();
}
}

// function to update comment:
void updateComment() 
{
int i,found=0;
char id[5];
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("UPDATE COMMENT",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(YELLOW_FG BOLD "   Enter Comment ID to update: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
for(i=0;i<commentCount;i++)
{
if(strcmp(comments[i].commentID,id)==0&&comments[i].is_used)
{
found=1;
printf(CYAN_FG BOLD "   Current Comment: %-79s\n" RESET,comments[i].commentText);
while(1)
{
printf(YELLOW_FG BOLD "   Enter new Comment Text: " RESET);
scanf(" %[^\n]",comments[i].commentText);
if(!check_input_validation(comments[i].commentText,11))
{
while(getchar()!='\n');
printf(RED_FG BOLD "   YOUR COMMENT IS TOO LONG... Please press enter and try again with max 70 characters.");
while(getchar()!='\n');
continue;
}
while(getchar()!='\n');
break;
}
saveCommentsToFile();
printf(GREEN_FG BOLD "\n   Comment updated successfully!\n" RESET);
pause();
return;
}
}
if(!found)
{
printf(RED_FG BOLD "\n   Comment ID not found!\n" RESET);
pause();
}
}

// Function to delete comment:
void deleteCommentByID() 
{
int i,j,found=0;
char id[5];
system("cls");
printf("\n\n\n\n\n");
printf(YELLOW_BBG MAGENTA_FG BOLD);
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(" ||==================================================================================================================|| \n");
print_centered_with_border("DELETE COMMENT",CONSOLE_WIDTH);
printf(" ||==================================================================================================================|| \n");
printf("                                                                                                                        \n");
printf("                                                                                                                        \n");
printf(RESET);
printf(YELLOW_FG BOLD "   Enter Comment ID to delete: " RESET);
scanf("%4s",id);
while(getchar()!='\n');
for(i=0;i<commentCount;i++)
{
if(strcmp(comments[i].commentID,id)==0&&comments[i].is_used)
{
found=1;
comments[i].is_used=0;
for(j=i;j<commentCount-1;j++)
comments[j]=comments[j+1];
commentCount--;
comments[commentCount].is_used=0;
saveCommentsToFile();
printf(GREEN_FG BOLD "\n   Comment deleted successfully!\n" RESET);
pause();
return;
}
}
if(!found)
{
printf(RED_FG BOLD "\n   Comment ID not found.\n" RESET);
pause();
}
}

//  SORTING :
//bubble sort to arrange comments with comment ID:
void sortByCommentID(int order) 
{
struct Comment temp;
int i,j;
for(i=0;i<commentCount-1;i++)
{
for(j=0;j<commentCount-i-1;j++)
{
if(comments[j].is_used&&comments[j+1].is_used)
{
if((strcmp(comments[j].commentID,comments[j+1].commentID)>0&&order==2)||(strcmp(comments[j].commentID,comments[j+1].commentID)<0&&order==3))
{             
temp=comments[j];
comments[j]=comments[j+1];
comments[j+1]=temp;
}
}
}
}
}

// FILE HANDLING:
void saveCommentsToFile() 
{
FILE *fp=fopen("comments.bin","wb");
if(fp==NULL) 
return;
fwrite(&commentCount,sizeof(int),1,fp);
fwrite(comments,sizeof(struct Comment),commentCount,fp);
fclose(fp);
}

void loadCommentsFromFile() 
{ 
FILE *fp=fopen("comments.bin","rb");
if(fp==NULL) 
return;
fread(&commentCount,sizeof(int),1,fp);
fread(comments,sizeof(struct Comment),commentCount,fp);
fclose(fp);
}

// Check if user exists:
int check_user_exists(char userID[5])
{
int i;
for(i=0;i<user_count;i++)
{
if(strcmp(users[i].id,userID)==0&&users[i].is_used)
return 1;
}
return 0;
}

// Check if task exists:
int check_task_exists(char taskID[5])
{
int i;
for(i=0;i<task_count;i++)
{
if(strcmp(tasks[i].taskID,taskID)==0&&tasks[i].is_used)
return 1;
}
return 0;
}
