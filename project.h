#ifndef PROJECT_H
#define PROJECT_H

#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

/*Log in window*/
class PersonInfo
{
public:
    string first_name;
    string last_name;
    string date_of_birth;
    string userName;
    string password;
    string credit_card_info;
    string credit_card_sn;
    string exprationDate;
    string checkingAccount_bal;
    string savingAccount_bal;


    void File_Read(string line);
};


class Login_window: public Gtk::Window{

public:
    string line_from_line;
    vector<PersonInfo> Customer_Information;
    ifstream inFile;
    Login_window();
    void verify_Account();
    virtual ~Login_window();

	//widgets
	Gtk::Image image;
	Gtk::Box box;
	Gtk::Entry entry1;
	Gtk::Label e1;
	Gtk::Label e2;
	Gtk::Label e3;
	Gtk::CheckButton checkbutton;
	Gtk::Label label1;
	Gtk::Label label2;
	Gtk::Box v1;
	Gtk::Box v2;
	Gtk::Entry entry2;

};

class forgot_window : public Gtk::Window
{
public:
    forgot_window(vector<PersonInfo>* Customer_Information);
    virtual ~forgot_window();

	vector<PersonInfo>* Copy_in;
	//int num;

	void change_Account();
    //void checkingTOsaving();
    //void savingTOchecking();
    //void close_button();

    Gtk::Box boxy;
    Gtk::Label l1;
	Gtk::Label l2;
	Gtk::Label l3;
	Gtk::Label l4;
	Gtk::Label l5;
    //Gtk::Box boxy;
    Gtk::Entry e1;
	Gtk::Entry e2;
	Gtk::Entry e3;
	Gtk::Button change;
    //Gtk::Button button_close, button_tosaving, button_tochecking;

};


class Person:public Login_window
{
public:
    std::string first_name;
    std::string last_name;
    std::string userName;
    std::string dateOfBirth;
    std::string newPassword;
    std::string creditCardNo;
    std::string exprationDate;
    std::string securityId;
    string checking;
    string saving;
    Gtk::Image image;
    Person(vector<PersonInfo>* Customer_Information);
	virtual ~Person();
};

/***************************************************************************************************************************/
/*sign up window*/
class Info_box:public Gtk::Window
{
public:
    Info_box(std::string first_name, std::string last_name, std::string dateOfBirth,
    std::string newPassword, std::string creditCardNo,
    std::string exprationDate, std::string securityId);
    virtual ~Info_box();

    Gtk::Label label, label1, label2, label3, label5,label6,label7;
    Gtk::Button register_button;
    Gtk::Grid grid;
    Gtk::VBox vbox;
    Gtk::HBox hbox;
    Gtk::Image image;
    Gtk::Box box;

protected:
    void register_function();
};

class Validator {
public:
    bool check_validity (std::string cardNumber);
};

/***********************************************************************************************************/
//main Window.h
class main_window :public Gtk::Window
{
public:
    main_window(vector<PersonInfo>& Customer_Information,string);
    vector<PersonInfo> ptr;
    string name1;
    string nam;
	int loop;
    virtual ~main_window();
    void displayChecking();
    void displaySaving();
    void underConstruct();
    void displayContact();
    void displayAppointment();
    void displayLocations();
    void set_opacity(double opacity);
	void signout();
    //widgets
    Gtk::Image image;
	Gtk::Frame left;
    Gtk::Label user;
    Gtk::Menu submenu1, submenu2,submenu3,submenu4;
    Gtk::MenuBar menubar;
    Gtk::MenuItem menufiles1,menufiles2,menufiles3,menufiles4,checking_account,saving_account,credit_card,between_ac,ac_at_bpp,ac_at_another,open_account,contact,appointment,locations;
    Gtk::SeparatorMenuItem line;
    Gtk::Box box;
    Gtk::Button sign_out;

};

/*******************************************************************************/
class Transfer1_window : public Gtk::Window
{
public:
    Transfer1_window(vector<PersonInfo>* Customer_Information,int nam);
    virtual ~Transfer1_window();

	vector<PersonInfo>* Copy_info;
	int num;

    void checkingTOsaving();
    void savingTOchecking();
    void close_button();

    Gtk::Box textb1;
    Gtk::Label title;
    Gtk::Box boxx;
    Gtk::Entry enter1;
    Gtk::Button button_close, button_tosaving, button_tochecking;

};
/***************************************************************************************/
class Transfer2_window : public Gtk::Window
{
public:
    Transfer2_window(vector<PersonInfo>* Customer_Information,int nam);
    virtual ~Transfer2_window();

	vector<PersonInfo>* Copy_info;
	int num;
	//string get_username;
	//int user_num;
    void close_button1();

    void TOuser();

    Gtk::Box textb2,textb3;
    Gtk::Label title1,title2;
    Gtk::Box boxy;
    Gtk::Entry enter2,enter3;
    Gtk::Button button_close1, button_transfer;

};
#endif
