//************ AC-51002 Software Development: Assignment 3 ***************
//************ Author: Jacob Ellis - 140014972			   ***************
// This program is designed to calculate the Basic Metabolic Rate (BMR) of an individual
// when given some basic information about that person. Calculations are based on user input factors such
// as age, height, weight, and gender. The program uses input and output file manipulation.
// The first question the user is asked, is whether they would like to create a profile,
// or whether they would like to view an existing profile. In creating a profile, users 
// are asked to provide a username, their age, height and weight. Lastly the user is asked which gender/sex they are
// which will determine the correct formula to apply in BMR calculations.
// The username chosen will determine the filename for their information to be output into (should they choose to save it).
// When selecting to view an existing profile, the user is asked for their username
// so that their information can be retrieved from the file of the same name. Users are told explicitly 
// not to include a space into their username.
// Initially, I had separated this program into header and additional .cpp files.
// In order to make marking easier, I have decided to keep everything in the main .cpp file
// so that the number of lines of code can be seen more easily. Tracing messages are signaled 
// by using multiple '%' signs before and after the comment. 
// Additionally - this program originally had more functionality, calculating Body Mass Index 
// (BMI) as well as BMR. This has been trimmed to fit the code line count for the assignment.
// Some of the 'call by reference' function parameters and class friend functions have been left in,
// to demonstrate that any further functionality could be easily implemented. 
// In order to test option2 (view existing profile), I have included an example .txt file. 
// To test this example profile, use "testusername" after choosing option 2. 


#include <iostream> 
#include<fstream>
using namespace std;

class Profile
{
private:
	string username;
	int age, height;
	double weight, BMR;
public: // The setter and getter functions work like typical setters and getters do. 
	void set_username(string); 
	string get_username();
	void set_age(int);
	int get_age();
	void set_height(int);
	int get_height();
	void set_BMR(double);
	double get_BMR();
	void set_weight(double);
	double get_weight();
	char gender;
	Profile();
	void output_to_screen();// This function outputs user input and BMR calculation to the screen.
	friend double maleBMRcalculator();
	friend double femaleBMRcalculator();
}; // This class creates a profile for the user to input information into 
int option, ageIn, heightIn;
double weightIn;
char YesOrNo;

Profile createProfileFunction(Profile&);// This function asks the user for their information.
void viewProfileFunction(Profile&); // This outputs the results and profile information to the screen.
void maleBMRcalculator(Profile&); // Performs the formula used to calculate BMR for males.
void femaleBMRcalculator(Profile&); // Performs the formula used to calculate BMR for females.
void printProfile(ofstream& file, Profile object); // This prints output user information to a .txt file based on username.
void viewExistingProfile(); // This reads a .txt file (based on username) and outputs it to the screen


int main()
{
	cout<< "Welcome to the incredible Basic Metabolic Rate (BMR) calculator!" << endl << endl << endl;
	cout << "Please indicate one of the following options by typing the option number (followed by pressing ENTER)" << endl<< endl;
	cout << " <<Option 1: Create a Profile>>\n \n <<Option 2: View an existing Profile>> \n";

	while (!(cin >> option) || (option < 0 || option>2)) // This validates the user choice.
	{
		cout << "INVALID OPTION! : Please enter a valid option from those listed.";
		cin.clear();
		cin.ignore(100, '\n');
		cout << " <<Option 1: Create a Profile>>\n <<Option 2: View an existing Profile>> \n";
	} 
	Profile CurrentUser; // This instantiates the current user object.

	switch (option) 
	{
	case 1:
		cout << "%%%% ENTERING INTO createProfileFunction() %%%%" << endl;
		createProfileFunction(CurrentUser); // This populates the object 'CurrentUser' with required information.
		viewProfileFunction(CurrentUser);
		cout << endl<< endl<<"Would you like to write this information to a text file ? ('Y' = Yes / 'N' = No)"<<endl;
		
		cin >> YesOrNo;
		YesOrNo = toupper(YesOrNo); // This converts the user input to the upper case form, before comparisons are made. 
		while (YesOrNo != 'Y' && YesOrNo != 'N')//Input validation for the question above
		{
			cin.clear();
			cin.ignore(100, '\n');
			cout << "!!!<<<Invalid input>>>!!!" << endl << "Please enter (Y) or (N) to indicate if you would like to print your BMR profile to a text file." << endl << endl;
			cin >> YesOrNo;
			YesOrNo = toupper(YesOrNo);
		}
		if (YesOrNo == 'Y') // If the user opts for yes, an output file will take this information. 
		{
			string filename;
			filename = CurrentUser.get_username(); // This assigns username to 'filename' variable.
			ofstream out_stream(filename + ".txt"); // This uses 'filename' to save this profile information to a .txt file.
			if (out_stream.is_open())
			{
				cout << "%%%%%%%(BEGINNING printProfile() TO CREATE OUTPUT FILE) %%%%%%%%" << endl;
				printProfile(out_stream, CurrentUser);// This outputs the information to the user defined file name.
				out_stream.close();
			}
			break;
		}
		else if (YesOrNo == 'N') // If the user chooses no, terminate program. 
		{
			break;
		}
	case 2: // This option allows the user to view a previously saved profile. 
		cout << "%%%%%(ENTERING INTO viewExistingProfile() FUNCTION)%%%%%%" << endl;
		viewExistingProfile();// This takes a .txt file and outputs it to the screen. 
		break; 
	}
}


void viewExistingProfile()
{
	string username;
	cout << "Please enter a username to retrieve the appropriate information: ";
	cin >> username;
	ifstream input_stream;
	input_stream.open(username + ".txt");
	cout << "%%%%%%(INPUT STREAM CREATED AT THIS STAGE (USING USERNAME VARIABLE)) %%%%%%%%"<< endl << endl;

	while (!(input_stream.is_open())) // This checks for a valid username and loops if not.
	{
		cout << "Username not found. Please ensure you input a valid username:  ";
		cin >> username;
		input_stream.open(username + ".txt");
	}
	if (input_stream.is_open()) // when given a valid username, this will trigger. 
	{
		cout << "%%%%%%%(FUNCTION TO READ FULL PROFILE INFO TO SCREEN BEGINS NOW)%%%%%%%" << endl;
		cout << input_stream.rdbuf();// This reads entire .txt file and outputs contents to screen.
		input_stream.close();
	}
}
void printProfile(ofstream& file, Profile object)// This function prints the information to an output file(.txt)
{
	file << "Username is : " << object.get_username() << endl;
	file << "Age is : " << object.get_age() << endl;
	file << "Height is: " << object.get_height() << "cm" << endl;
	file << "Weight is: " << object.get_weight() << "Kg" << endl << endl;
	file <<"Your calculated BMR is : " << object.get_BMR() << " calories per day (without accounting for any exercise)" << endl;
}
void maleBMRcalculator(Profile& object)
{	// MEN : BMR(metric) = (10 × weight in kg) + (6.25 × height in cm) - (5 × age in years) + 5
	cout << "%%%%%%(FUNCTION maleBMRcalculator() begins now)%%%%%%" << endl;
	double weight = object.get_weight();
	double height = object.get_height();
	double age = object.get_age();
	double BMR = (10 * weight) + (6.25 * height) - (5 * age) + 5;
	object.set_BMR(BMR);
}
void femaleBMRcalculator(Profile& object) 
{
	// WOMEN : BMR (metric) = (10 × weight in kg) + (6.25 × height in cm) - (5 × age in years) - 161
	cout << "%%%%%%(FUNCTION femaleBMRcalculator() begins now)%%%%%%" << endl<< endl;
	double weight = object.get_weight();
	double height = object.get_height();
	double age = object.get_age();
	long double BMR = (10 * weight) + (6.25 * height) - (5 * age) - 161;
	object.set_BMR(BMR);
} 
Profile createProfileFunction(Profile& object)
{
	string usernameIn;
	cout << "Please enter a username (followed by pressing ENTER) :  " << endl << "***(Please make sure there are no spaces used in this!)***" << endl;
	cin >> usernameIn;
	object.set_username(usernameIn);
	cout << endl << endl<< "Please enter your age:  ";
	while (!(cin >> ageIn) || (ageIn < 0 || ageIn > 150))// This validates user input, and checks for ludicrous values
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Please enter a valid age to proceed:   " ;
	}
	object.set_age(ageIn);
	cout << endl<<endl<< "Please enter your height (in centimeters) :  ";
	while (!(cin >> heightIn) || (heightIn > 250 || heightIn < 100))// This validates user input, and checks for ludicrous values
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Please enter a valid height (in centimeters) :  ";
	}
	object.set_height(heightIn);
	cout << endl<<endl<< "Please enter your weight (in kilograms) :  ";
	while (!(cin >> weightIn) || (weightIn > 300 || weightIn < 0))// This validates user input, and checks for ludicrous values
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Please enter a valid weight (in kilograms) :  ";
	}
	object.set_weight(weightIn);
	cout << endl << endl<< "Are you Male or Female? (Answer 'M' for Male / 'F' for Female)"; // This decides which formula to use in BMR calculations.
	cin >> object.gender;
	object.gender = toupper(object.gender); // This converts the user input to the upper case form, before comparisons are made. 
	while (object.gender != 'M' && object.gender != 'F')//Input validation for the question above
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "!!!<<<Invalid input>>>!!!" << endl << "Please enter (M) or (F) to indicate your gender." << endl;
		cin >> object.gender;
		object.gender= toupper(object.gender);
	}
	if (object.gender == 'M') 
	{
		maleBMRcalculator(object);
	}
	else if (object.gender== 'F')
	{
		femaleBMRcalculator(object);
	}
	return object;
}
void viewProfileFunction(Profile& object)
{
	object.output_to_screen();
}
void Profile::set_username(string x)
{
	username = x;
}
string Profile::get_username()
{
	return username;
}
void Profile::set_age(int x)
{
	age = x;
}
int Profile::get_age()
{
	return age;
}
void Profile::set_height(int x)
{
	height = x;
}
int Profile::get_height()
{
	return height;
}
void Profile::set_BMR(double x)
{
	BMR = x;
}
double Profile::get_BMR()
{
	return BMR;
}
void Profile::set_weight(double x)
{
	weight = x;
}
double Profile::get_weight()
{
	return weight;
}
Profile:: Profile()
{
	set_username("EMPTY");
	set_age(0);
	set_height(0);
	set_BMR(0);
	set_weight(0.00);
}
void Profile::output_to_screen()
{
	cout << endl<<endl<< "Username is : " << username << endl;
	cout << "Age is : " << age << endl;
	cout << "Height is: " << height <<"cm"<< endl;
	cout << "Weight is: " << weight << "Kg" << endl << endl;
	cout << "Your calculated BMR is : " << BMR << " calories per day (without accounting for any exercise)" << endl;
}

