#include <iostream>
#include "project.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

void PersonInfo::File_Read(string line)
{
        string intermidiate;
        stringstream ss(line);
        getline(ss,intermidiate,',');
        first_name = intermidiate;

        getline(ss,intermidiate,',');
        last_name = intermidiate;

        getline(ss,intermidiate,',');
        userName = intermidiate;

        getline(ss,intermidiate,',');
        date_of_birth = intermidiate;

        getline(ss,intermidiate,',');
        password = intermidiate;

        getline(ss,intermidiate,',');
        credit_card_info = intermidiate;

		getline(ss,intermidiate,',');
        credit_card_sn = intermidiate;

		getline(ss,intermidiate,',');
		exprationDate = intermidiate;

        getline(ss,intermidiate,',');
        checkingAccount_bal = intermidiate;

        getline(ss,intermidiate,',');
        savingAccount_bal = intermidiate;

}
Login_window::Login_window():box(Gtk::ORIENTATION_VERTICAL)
{

    inFile.open("customer.txt");

    while(!inFile.eof())
    {
        PersonInfo P;
        getline(inFile,line_from_line);
        P.File_Read(line_from_line);
        Customer_Information.push_back(P);
    }


    set_size_request(300,600);
    set_border_width(80);
    set_title("--BANK++--");

    add(box);
    image.set("im.png");
    image.set_pixel_size(15);
    box.pack_start(image);

    e2.set_text("");
    v2.pack_start(e2);

	e3.set_text("");
	box.pack_start(e3);

    label1.set_text("Enter your username:                                                                                                                                                  ");
    label1.set_opacity(1);
    box.pack_start(label1);

    entry1.set_max_length(50);
    entry1.select_region(0,entry1.get_text_length());
    box.pack_start(entry1);
      
    label2.set_text("Enter your password:                                                                                                                                                 ");
    box.pack_start(label2);

    entry2.set_max_length(50);
    entry2.select_region(0,entry2.get_text_length());
    box.pack_start(entry2);
    entry2.set_visibility(false);

    Gtk::Button* button = new Gtk::Button("Log In");
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(
    "button {background-image: image(gold);}\
     button:hover {background-image: image(red);}\
     button:active {background-image: image(brown);}");
    button->get_style_context()->add_provider(
    css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button->signal_pressed().connect(sigc::mem_fun(*this,&Login_window::verify_Account));
    v1.pack_start(*button);

    Gtk::Button* button1 = new Gtk::Button("Sign Up");
    Glib::RefPtr<Gtk::CssProvider> css_provider1 = Gtk::CssProvider::create();
    css_provider1->load_from_data(
    "button {background-image: image(gold);}\
     button:hover {background-image: image(red);}\
     button:active {background-image: image(brown);}");
    button1->get_style_context()->add_provider(
    css_provider1, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button1->signal_pressed().connect([this]
                                    {
                                        Person p(&Customer_Information);
                                    });
    v1.pack_start(*button1);

    e1.set_text("");
    box.pack_start(e1);
    box.pack_start(v1);

    Gtk::Button *forgot = new Gtk::Button("Forgot Password?");
    Glib::RefPtr<Gtk::CssProvider> css_provider3 = Gtk::CssProvider::create();
    css_provider3->load_from_data(
    "button {background-image: image(gold);}\
     button:hover {background-image: image(red);}\
     button:active {background-image: image(brown);}");
    forgot->get_style_context()->add_provider(
    css_provider3, GTK_STYLE_PROVIDER_PRIORITY_USER);
    forgot->signal_clicked().connect([this]
    {
		hide();
        forgot_window w1(&Customer_Information);
        Gtk::Main::run(w1);
    });

    //v1.pack_start(*forgot);
	box.pack_start(*forgot);

    show_all_children();
}

forgot_window::forgot_window(vector<PersonInfo>* Customer_Information):boxy(Gtk::ORIENTATION_VERTICAL)
{
    set_size_request(400,300);
    set_border_width(40);
	add(boxy);
    set_title("---Forgot Password---");

	Copy_in = Customer_Information;

    l1.set_text("Please answer the following security questions: \n");
	boxy.pack_start(l1);
	l2.set_text("Your Date of Birth: ");
	boxy.pack_start(l2);
	e1.set_max_length(10);
	e1.select_region(0,e1.get_text_length());
	boxy.pack_start(e1);

	l3.set_text("Your username:      ");
	boxy.pack_start(l3);
	e2.set_max_length(20);
	e2.select_region(0,e2.get_text_length());
	boxy.pack_start(e2);

	l4.set_text("Your new Password:  ");
	boxy.pack_start(l4);
	e3.set_max_length(20);
	e3.select_region(0,e3.get_text_length());
	boxy.pack_start(e3);
	l5.set_text("");
	boxy.pack_start(l5);

	Gtk::Button* change = new Gtk::Button("Change");
    Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data(
    "button {background-image: image(gold);}\
     button:hover {background-image: image(red);}\
     button:active {background-image: image(brown);}");
    change->get_style_context()->add_provider(
    css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
    change->signal_pressed().connect(sigc::mem_fun(*this,&forgot_window::change_Account));
    boxy.pack_start(*change);

    show_all_children();
}
forgot_window::~forgot_window(){
}

void forgot_window::change_Account(){

	int status=0;
	for(int i=0;i<Copy_in->size();i++){
		if(e1.get_text()==Copy_in->at(i).date_of_birth && e2.get_text()==Copy_in->at(i).userName){
			Copy_in->at(i).password=e3.get_text();
			status=1;
			i=Copy_in->size()+1;
		}
		else if(i==(Copy_in->size()-1))
        {
            Gtk::MessageDialog dialog3( *this,"",false,Gtk::MESSAGE_WARNING);
            dialog3.set_secondary_text("Your security answers doesn't match!!!");
            dialog3.run();
        }
	}

	if(status==1){
		ofstream fileOutput("customer.txt");

		for(int k=0; k<Copy_in->size(); k++){
			fileOutput<<Copy_in->at(k).first_name<<","<<Copy_in->at(k).last_name<<","<<Copy_in->at(k).userName<<","<<Copy_in->at(k).date_of_birth<<","<<Copy_in->at(k).password<<","<<Copy_in->at(k).credit_card_info<<","<<Copy_in->at(k).credit_card_sn<<","<<Copy_in->at(k).exprationDate<<","<<Copy_in->at(k).checkingAccount_bal<<","<<Copy_in->at(k).savingAccount_bal<<"\n";
		}

		Gtk::MessageDialog dialog3( *this,"",false,Gtk::MESSAGE_INFO);
        dialog3.set_secondary_text("Your security answers matched. Password changed successfully");
        dialog3.run();

	}
	hide();
	Login_window w;
	Gtk::Main::run(w);

}

void Login_window::verify_Account()
{

    for(int i=0; i<Customer_Information.size(); i++)
    {
		if(entry1.get_text()=="" || entry2.get_text()==""){
			Gtk::MessageDialog dialog3( *this,"",false,Gtk::MESSAGE_WARNING);
            dialog3.set_secondary_text("The field is EMPTY!!");
            dialog3.run();
			i=Customer_Information.size()+1;
		}

        else if((entry1.get_text()==Customer_Information[i].userName)&&(entry2.get_text()==Customer_Information[i].password))
        {
			hide();
            main_window window(Customer_Information,entry1.get_text());
            Gtk::Main::run(window);
            i=Customer_Information.size()+1;
        }
        else if(i==(Customer_Information.size()-1))
        {
            Gtk::MessageDialog dialog3( *this,"",false,Gtk::MESSAGE_WARNING);
            dialog3.set_secondary_text("Wrong Password.");
            dialog3.run();
        }

    }

}

Login_window::~Login_window()
{
}

bool check_validity (string cardNumber)
{
    int lastDigit;
    vector <int> creditL;

    for (int i = 0; i < cardNumber.size(); i++)
    {
        char a=cardNumber[i];
        int r= a - '0';
        creditL.push_back(r);
    }

    lastDigit=creditL[((cardNumber.size())-1)];

    for (int i=(creditL.size())-2; i>= 0; i=i- 2)
    {
        int MultiplyOdd = creditL[i];
        MultiplyOdd = MultiplyOdd * 2;
        if (MultiplyOdd > 9) {
            MultiplyOdd = MultiplyOdd % 10 + 1;
        }
        creditL[i]=MultiplyOdd;
    }

    int sum = 0;
    for (int i = 0; i < (creditL.size())-1; i++)
    {
        sum += creditL[i];
    }

    int m=sum % 10;
    int x;
    if(m==0)
    {
        x=0;
    }
    else
    {
        x=10-m;
    }

    if (x == lastDigit)
    {
         return true;
    }

    else
    {
        return false;
    }
}
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/

Person::Person(vector<PersonInfo>* Customer_Information)
{
    Gtk::Window w;

    Gtk::Dialog *dialog = new Gtk::Dialog();
    dialog->set_transient_for(w);
    dialog->set_size_request(400, 500);
    dialog->set_border_width(50);
    dialog->set_title("Sign Up Form");

    Gtk::Label *label = new Gtk::Label("Enter first name:");
    dialog->get_content_area()->pack_start(*label);
    label->show();



    dialog->add_button("Cancel", 0);

    dialog->add_button("Register",1);
    dialog->set_default_response(1);

    Gtk::Entry *entry_first = new Gtk::Entry();
    //entry_first->set_text("First Name");
    entry_first->set_max_length(50);
    entry_first->show();
    dialog->get_vbox()->pack_start(*entry_first);

    Gtk::Label *label1 = new Gtk::Label("Enter last name:");
    dialog->get_content_area()->pack_start(*label1);
    label1->show();

    Gtk::Entry *entry_last = new Gtk::Entry();
    //entry_last->set_text("Last Name");
    entry_last->set_max_length(50);
    entry_last->show();
    dialog->get_vbox()->pack_start(*entry_last);

    Gtk::Label *label8 = new Gtk::Label("Create user name:");
    dialog->get_content_area()->pack_start(*label8);
    label8->show();

    Gtk::Entry *entry_username = new Gtk::Entry();
    entry_username->set_max_length(50);
    entry_username->show();
    dialog->get_vbox()->pack_start(*entry_username);

    Gtk::Label *label2 = new Gtk::Label("Date of Birth:");
    dialog->get_content_area()->pack_start(*label2);
    label2->show();

    Gtk::Entry *entry_date = new Gtk::Entry();
    entry_date->set_max_length(50);
    entry_date->show();
    dialog->get_vbox()->pack_start(*entry_date);

    Gtk::Label *label3 = new Gtk::Label("New Password:");
    dialog->get_content_area()->pack_start(*label3);
    label3->show();

    Gtk::Entry *entry_password = new Gtk::Entry();
    entry_password->set_visibility(false);
    entry_password->set_max_length(50);
    entry_password->show();
    dialog->get_vbox()->pack_start(*entry_password);

    Gtk::Label *label5 = new Gtk::Label("Debit Card Number:");
    dialog->get_content_area()->pack_start(*label5);
    label5->show();

    Gtk::Entry *entry_creditCardNo = new Gtk::Entry();
    entry_creditCardNo->set_max_length(50);
    entry_creditCardNo->show();
    dialog->get_vbox()->pack_start(*entry_creditCardNo);

    Gtk::Label *label6 = new Gtk::Label("Expiration date");
    dialog->get_content_area()->pack_start(*label6);
    label6->show();

    Gtk::Entry *entry_expDate = new Gtk::Entry();
    entry_expDate->set_max_length(50);
    entry_expDate->show();
    dialog->get_vbox()->pack_start(*entry_expDate);

    Gtk::Label *label7 = new Gtk::Label("Security ID");
    dialog->get_content_area()->pack_start(*label7);
    label7->show();

    Gtk::Entry *entry_securityId = new Gtk::Entry();
    entry_securityId->set_max_length(50);
    entry_securityId->show();
    dialog->get_vbox()->pack_start(*entry_securityId);

    dialog->close();
    int result = dialog->run();

	PersonInfo z;
    z.first_name = entry_first->get_text();
    z.last_name = entry_last->get_text();
    z.userName = entry_username->get_text();
    z.date_of_birth = entry_date->get_text();
    z.password = entry_password->get_text();
    z.credit_card_info = entry_creditCardNo->get_text();
    z.exprationDate=entry_expDate->get_text();
    z.credit_card_sn=entry_securityId->get_text();
    z.checkingAccount_bal = "100";
    z.savingAccount_bal = "0";

	bool val= check_validity(entry_creditCardNo->get_text());
    ofstream fileOutput("customer.txt",std::ios::app);

    if(val==false)
    {
        Gtk::MessageDialog dialog3( *this,"",false,Gtk::MESSAGE_WARNING);
        dialog3.set_secondary_text("Opps! Not a valid card.");
        dialog3.run();
    }
    else
    {
		Customer_Information->push_back(z);
        fileOutput<<z.first_name<<","<<z.last_name<<","<<z.userName<<","<<z.date_of_birth<<","<<z.password<<","<<z.credit_card_info<<","<<z.exprationDate<<","<<z.credit_card_sn<<","<<z.checkingAccount_bal<<","<<z.savingAccount_bal<<"\n";
    }
    delete dialog;
    delete label;
    delete label1;
    delete label2;
    delete label3;
    delete label5;
    delete label6;
    delete label7;
    delete label8;
    delete entry_first;
    delete entry_last;
    delete entry_date;
    delete entry_password;
    delete entry_creditCardNo;
    delete entry_expDate;
    delete entry_securityId;
    delete entry_username;
}

Person::~Person()
{
}

Info_box::Info_box(std::string first_name, std::string last_name, std::string dateOfBirth,
    std::string newPassword, std::string creditCardNo,
    std::string exprationDate, std::string securityId)
{
    set_title("--Registered Person--");
    set_size_request(400, 600);

    add(vbox);

    label.set_text("First name: "+first_name);
    label.set_padding(10,10);
    vbox.pack_start(label);

    label1.set_text("Last name: "+last_name);
    label1.set_padding(10,10);
    vbox.pack_start(label1);

    label2.set_text("Date of Birth: "+dateOfBirth);
    label2.set_padding(10,10);
    vbox.pack_start(label2);

    label3.set_text("New Password: "+newPassword);
    label3.set_padding(10,10);
    vbox.pack_start(label3);

    label5.set_text("Credit Card Number: "+creditCardNo);
    label5.set_padding(10,10);
    vbox.pack_start(label5);

    label6.set_text("Expiration File: "+exprationDate);
    label6.set_padding(10,10);
    vbox.pack_start(label6);

    label7.set_text("Security ID: "+securityId);
    label7.set_padding(10,10);
    vbox.pack_start(label7);

    register_button.set_label("Confirm");
    register_button.signal_pressed().connect(sigc::mem_fun(*this,&Info_box::register_function));
    vbox.pack_start(register_button);

    show_all_children();
}

Info_box::~Info_box(){};

void Info_box::register_function()
{
    hide();
}
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
/*****************************************************************************************************************/
main_window::main_window(vector<PersonInfo> &Customer_Information,string uname):box(Gtk::ORIENTATION_VERTICAL),sign_out("Sign Out"),left("")
{
    set_size_request(500,400);
    set_border_width(30);
    ptr = Customer_Information;
    name1=uname;
    set_title("$$$$ BANK++ $$$$");

    add(box);
    for (int i=0;i<ptr.size();i++)
    {
        if(name1==ptr[i].userName)
        {
            nam = ptr[i].first_name;
			loop=i;
        }
    }


	//user.set_justify(Gtk::JUSTIFY_RIGHT);

	user.set_justify(Gtk::JUSTIFY_LEFT);
	user.set_label("Hello "+nam+",                                                                                                                                ");
	user.set_pattern (
          "_____________________________________________________________________________________________________________________________________________________________");

	//user.set_justify(Gtk::JUSTIFY_FILL);
	//user.set_line_wrap();

	//left.add(user);
    box.pack_start(user);

    box.pack_start(menubar);

    //Top Menu bar
    menufiles1.set_label("Accounts");
    menubar.append(menufiles1);

    menufiles2.set_label("Transfer");
    menubar.append(menufiles2);

    menufiles3.set_label("Open Account");
    menubar.append(menufiles3);

    menufiles4.set_label("Help & Support");
    menubar.append(menufiles4);

    //sub-menu for Accounts
    menufiles1.set_submenu(submenu1);

    checking_account.set_label("Checking Account");
    //checking_account.set_opacity(1);
    checking_account.signal_activate().connect([this]{this->displayChecking();});
    submenu1.append(checking_account);

    saving_account.set_label("Saving Account");
    saving_account.signal_activate().connect([this]{this->displaySaving();});
    submenu1.append(saving_account);

    credit_card.set_label("Credit Card");
    submenu1.append(credit_card);

    //sub-menu for Transfer
    menufiles2.set_submenu(submenu2);
    between_ac.set_label("Between Your Acocunts");
    between_ac.signal_activate().connect([this]
    {
        Transfer1_window w1(&this->ptr,loop);
        Gtk::Main::run(w1);
    });
    submenu2.append(between_ac);

    ac_at_bpp.set_label("Account at Bank ++");
    ac_at_bpp.signal_activate().connect([this]
    {
        Transfer2_window w2(&this->ptr,loop);
        Gtk::Main::run(w2);
    });

    submenu2.append(ac_at_bpp);

    ac_at_another.set_label("Account at Another Bank");
    submenu2.append(ac_at_another);

    //sub-menu for Open Account
    menufiles3.set_submenu(submenu3);
    open_account.set_label("Open new Account");
    open_account.signal_activate().connect([this]{this->underConstruct();});
    submenu3.append(open_account);

    //sub-menu for Help & Support
    menufiles4.set_submenu(submenu4);
    contact.set_label("Contact Us");
    contact.signal_activate().connect([this]{this->displayContact();});
    submenu4.append(contact);

    appointment.set_label("Schedule an appointment");
    appointment.signal_activate().connect([this]{this->displayAppointment();});
    submenu4.append(appointment);

    locations.set_label("Locations");
    locations.signal_activate().connect([this]{this->displayLocations();});
    submenu4.append(locations);

    image.set("image.jpg");
    box.pack_start(image);

    Gtk::Button* button3 = new Gtk::Button("Sign Out");
    Glib::RefPtr<Gtk::CssProvider> css_provider2 = Gtk::CssProvider::create();
    css_provider2->load_from_data(
    "button {background-image: image(gold);}\
     button:hover {background-image: image(red);}\
     button:active {background-image: image(brown);}");
    button3->get_style_context()->add_provider(
    css_provider2, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button3->signal_pressed().connect(sigc::mem_fun(*this,&main_window::signout));
    box.pack_start(*button3);


    show_all_children();


}

void main_window::signout(){

	hide();
	//hide();

	Login_window ww;
	Gtk::Main::run(ww);
}

void main_window::displayChecking()
{
    Gtk::MessageDialog dialog3( *this,"Checking Account Balance",false,Gtk::MESSAGE_INFO);
    for(int i =0; i<ptr.size(); i++)
	{
		if(name1==ptr[i].userName)
		{
            string checking="You currently have $"+ ptr[i].checkingAccount_bal;
            dialog3.set_secondary_text(checking);
            dialog3.run();
            i = ptr.size()+1;
		}
	}
}

void main_window::displaySaving()
{
    Gtk::MessageDialog dialog4(*this, "Saving Account Balance",false,Gtk::MESSAGE_INFO);
	for(int i =0; i<ptr.size(); i++)
	{
		if(name1==ptr[i].userName)
		{
            string saving="You currently have $"+ ptr[i].savingAccount_bal;
            dialog4.set_secondary_text(saving);
            dialog4.run();
            i = ptr.size()+1;
		}
	}

}
void main_window::underConstruct()
{
    Gtk::MessageDialog dialog5( *this,"",false,Gtk::MESSAGE_INFO);
    dialog5.set_secondary_text("Page Under Construction!!!");
    dialog5.run();
}
void main_window::displayContact()
{
    Gtk::MessageDialog dialog6( "Contact us at:",false,Gtk::MESSAGE_INFO);
    dialog6.set_secondary_text("Email: bankplusplus.com, Phone: 817-bank-plus");
    dialog6.run();
}
void main_window::displayAppointment()
{
    Gtk::MessageDialog dialog7( *this,"Information",false,Gtk::MESSAGE_INFO);
    dialog7.set_secondary_text("Page Under Construction!!!");
    dialog7.run();
}
void main_window::displayLocations()
{
    Gtk::MessageDialog dialog8(*this, "Information",false,Gtk::MESSAGE_INFO);
    dialog8.set_secondary_text("Arlington,TX,76019");
    dialog8.run();
}

main_window::~main_window()
{
}

/*****************************************************************************************************/
Transfer1_window::Transfer1_window(vector<PersonInfo>* Customer_Information, int na):boxx(Gtk::ORIENTATION_VERTICAL)
{
    set_size_request(400,300);
    set_border_width(40);
    set_title("---Transfer---");

	Copy_info = Customer_Information;
	num=na;

    add(boxx);


    title.set_text("Enter the amount");
    boxx.pack_start(title);

    enter1.set_max_length(10);
    enter1.set_text("");
    enter1.select_region(0,enter1.get_text_length());
    boxx.pack_start(enter1);

    boxx.pack_start(textb1);

    Gtk::Button* button_tosaving = new Gtk::Button("From Checking to Saving");
    Glib::RefPtr<Gtk::CssProvider> css_provider2 = Gtk::CssProvider::create();
    css_provider2->load_from_data(
    "button {background-image: image(gold);}\
     button:hover {background-image: image(red);}\
     button:active {background-image: image(brown);}");
    button_tosaving->get_style_context()->add_provider(css_provider2, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button_tosaving->signal_clicked().connect(sigc::mem_fun(*this,&Transfer1_window::checkingTOsaving));
    boxx.pack_start(*button_tosaving);


    Gtk::Button* button_tochecking = new Gtk::Button("From Saving to Checking");
    button_tochecking->get_style_context()->add_provider(css_provider2, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button_tochecking->signal_clicked().connect(sigc::mem_fun(*this,&Transfer1_window::savingTOchecking));
    boxx.pack_start(*button_tochecking);


    Gtk::Button* button_close = new Gtk::Button("Close");
    button_close->get_style_context()->add_provider(css_provider2, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button_close->signal_clicked().connect( sigc::mem_fun(*this,&Transfer1_window::close_button));
    boxx.pack_start(*button_close);

    button_close->set_can_default();
    button_close->grab_default();

    show_all_children();
}

Transfer1_window::~Transfer1_window()
{
}


void Transfer1_window::checkingTOsaving()
{

    string input=enter1.get_text();
    int a = stoi(input);
	int b = stoi(Copy_info->at(num).checkingAccount_bal);
	int s = stoi(Copy_info->at(num).savingAccount_bal);
	if(a>b){
		Gtk::MessageDialog dialog5( *this,"",false,Gtk::MESSAGE_INFO);
            string checking="Sorry!!! You donot have sufficient fund!";
            dialog5.set_secondary_text(checking);
            dialog5.run();

	}
	else{
	b=b-a;
	s = s+a;
	ostringstream ss,sk;
    ss << b;
	sk << s;

	Copy_info->at(num).checkingAccount_bal=ss.str();
	Copy_info->at(num).savingAccount_bal=sk.str();

	ofstream fileOutput("customer.txt");

	for(int k=0; k<Copy_info->size(); k++){
		fileOutput<<Copy_info->at(k).first_name<<","<<Copy_info->at(k).last_name<<","<<Copy_info->at(k).userName<<","<<Copy_info->at(k).date_of_birth<<","<<Copy_info->at(k).password<<","<<Copy_info->at(k).credit_card_info<<","<<Copy_info->at(k).credit_card_sn<<","<<Copy_info->at(k).exprationDate<<","<<Copy_info->at(k).checkingAccount_bal<<","<<Copy_info->at(k).savingAccount_bal<<"\n";
	}

    Gtk::MessageDialog dialog5( *this,"",false,Gtk::MESSAGE_INFO);
            string checking="Transfer Successful!! You sent $"+ input+" from your checking to saving account.";
            dialog5.set_secondary_text(checking);
            dialog5.run();
	}

}

void Transfer1_window::savingTOchecking()
{
    string input=enter1.get_text();
    int a = stoi(input);
	int b = stoi(Copy_info->at(num).checkingAccount_bal);
	int s = stoi(Copy_info->at(num).savingAccount_bal);

	if(a>s){
		Gtk::MessageDialog dialog5( *this,"",false,Gtk::MESSAGE_INFO);
            string checking="Sorry!!! You donot have sufficient fund!";
            dialog5.set_secondary_text(checking);
            dialog5.run();

	}
	else{
	b=b+a;
	s = s-a;
	ostringstream ss,sk;
    ss << b;
	sk << s;

	Copy_info->at(num).checkingAccount_bal=ss.str();
	Copy_info->at(num).savingAccount_bal=sk.str();

	ofstream fileOutput("customer.txt");

	for(int k=0; k<Copy_info->size(); k++){
		fileOutput<<Copy_info->at(k).first_name<<","<<Copy_info->at(k).last_name<<","<<Copy_info->at(k).userName<<","<<Copy_info->at(k).date_of_birth<<","<<Copy_info->at(k).password<<","<<Copy_info->at(k).credit_card_info<<","<<Copy_info->at(k).credit_card_sn<<","<<Copy_info->at(k).exprationDate<<","<<Copy_info->at(k).checkingAccount_bal<<","<<Copy_info->at(k).savingAccount_bal<<"\n";
	}

	Gtk::MessageDialog dialog5( *this,"",false,Gtk::MESSAGE_INFO);
            string checking="Transfer Successful!! You sent $"+ input+" from your saving to checking account.";
            dialog5.set_secondary_text(checking);
            dialog5.run();
	}
}

void Transfer1_window::close_button()
{
hide();
}

Transfer2_window::Transfer2_window(vector<PersonInfo>* Customer_Information, int na):boxy(Gtk::ORIENTATION_VERTICAL)
{
    set_size_request(400,300);
    set_border_width(40);
    set_title("---Transfer---");

	Copy_info = Customer_Information;
	num=na;

    add(boxy);

    title1.set_text("Enter the amount");
    boxy.pack_start(title1);

    enter2.set_max_length(10);
    enter2.set_text("");
    enter2.select_region(0,enter2.get_text_length());
    boxy.pack_start(enter2);

    boxy.pack_start(textb2);

        title2.set_text("Enter the username");
    boxy.pack_start(title2);

    enter3.set_max_length(50);
    enter3.set_text("");
    enter3.select_region(0,enter3.get_text_length());
    boxy.pack_start(enter3);
    boxy.pack_start(textb3);

    Gtk::Button* button_transfer = new Gtk::Button("Transfer");
    Glib::RefPtr<Gtk::CssProvider> css_provider2 = Gtk::CssProvider::create();
    css_provider2->load_from_data(
    "button {background-image: image(gold);}\
     button:hover {background-image: image(red);}\
     button:active {background-image: image(brown);}");
    button_transfer->get_style_context()->add_provider(css_provider2, GTK_STYLE_PROVIDER_PRIORITY_USER);
   button_transfer->signal_clicked().connect(sigc::mem_fun(*this,&Transfer2_window::TOuser));
    boxy.pack_start(*button_transfer);


    Gtk::Button* button_close1 = new Gtk::Button("Close");
    button_close1->get_style_context()->add_provider(css_provider2, GTK_STYLE_PROVIDER_PRIORITY_USER);
    button_close1->signal_clicked().connect( sigc::mem_fun(*this,&Transfer2_window::close_button1));
    boxy.pack_start(*button_close1);

    button_close1->set_can_default();
    button_close1->grab_default();

    show_all_children();
}

Transfer2_window::~Transfer2_window()
{
}


void Transfer2_window::TOuser()
{
    string input=enter2.get_text();
    int a = stoi(input);
	int b = stoi(Copy_info->at(num).checkingAccount_bal);
	int user_num;
	int status=2;
	string get_username=enter3.get_text();
	for(int j=0;j<Copy_info->size();j++){
		if(get_username==Copy_info->at(j).userName){
			user_num=j;
			status=1;
			j=Copy_info->size()+1;
		}
		 else if(j==(Copy_info->size()-1))
        {
            Gtk::MessageDialog dialog3( *this,"",false,Gtk::MESSAGE_WARNING);
            dialog3.set_secondary_text("There is no such username!!!");
            dialog3.run();
        }
	}
	if(status==1){
		int s=stoi(Copy_info->at(user_num).checkingAccount_bal);


		if(a>b){
			Gtk::MessageDialog dialog5( *this,"",false,Gtk::MESSAGE_INFO);
            string checking="Sorry!!! You donot have sufficient fund!";
            dialog5.set_secondary_text(checking);
            dialog5.run();

		}

		else{
			b=b-a;
			s=s+a;
			ostringstream ss,sk;
			ss << b;
			sk << s;

			Copy_info->at(num).checkingAccount_bal=ss.str();
			Copy_info->at(user_num).checkingAccount_bal=sk.str();

			ofstream fileOutput("customer.txt");

			for(int k=0; k<Copy_info->size(); k++){

				fileOutput<<Copy_info->at(k).first_name<<","<<Copy_info->at(k).last_name<<","<<Copy_info->at(k).userName<<","<<Copy_info->at(k).date_of_birth<<","<<Copy_info->at(k).password<<","<<Copy_info->at(k).credit_card_info<<","<<Copy_info->at(k).credit_card_sn<<","<<Copy_info->at(k).exprationDate<<","<<Copy_info->at(k).checkingAccount_bal<<","<<Copy_info->at(k).savingAccount_bal<<"\n";
			}

			Gtk::MessageDialog dialog5( *this,"",false,Gtk::MESSAGE_INFO);
            string checking="Transfer Successful!! You sent $"+ input+" to user " +Copy_info->at(user_num).userName;
            dialog5.set_secondary_text(checking);
            dialog5.run();
		}
	}

}

void Transfer2_window::close_button1()
{
    hide();
}

