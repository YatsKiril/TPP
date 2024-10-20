#pragma once
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class VideoGame {
	public:
		int id;
		String^ title;
		String^ genre;
		int releaseYear;
		String^ platform;
		String^ developer;

		VideoGame(int id, String^ title, String^ genre, int releaseYear, String^ platform, String^ developer) {
			this->id = id;
			this->title = title;
			this->genre = genre;
			this->releaseYear = releaseYear;
			this->platform = platform;
			this->developer = developer;
		}

		virtual String^ ToString() override {
			return String::Format("{0} - {1} - {2} - {3} - {4} - {5}",
				id, title, genre, releaseYear, platform, developer);
		}
	};

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			LoadData();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;
		List<VideoGame^>^ games; 
		int nextId = 1; 

		ListBox^ gamesListBox;
		TextBox^ titleTextBox;
		TextBox^ genreTextBox;
		TextBox^ releaseYearTextBox;
		TextBox^ platformTextBox;
		TextBox^ developerTextBox;
		Button^ addButton;
		Button^ updateButton;
		Button^ deleteButton;
		MenuStrip^ menuStrip;
		ToolStripMenuItem^ fileMenu;
		ToolStripMenuItem^ aboutMenuItem;
		ToolStripMenuItem^ exitMenuItem;

		String^ titlePlaceholder = "Title";
		String^ genrePlaceholder = "Genre";
		String^ releaseYearPlaceholder = "Release Year";
		String^ platformPlaceholder = "Platform";
		String^ developerPlaceholder = "Developer";

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(500, 400);
			this->Text = L"Video Game Catalog";
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			this->menuStrip = gcnew MenuStrip();
			this->fileMenu = gcnew ToolStripMenuItem(L"File");
			this->aboutMenuItem = gcnew ToolStripMenuItem(L"About");
			this->exitMenuItem = gcnew ToolStripMenuItem(L"Exit");

			this->fileMenu->DropDownItems->Add(this->aboutMenuItem);
			this->fileMenu->DropDownItems->Add(this->exitMenuItem);
			this->menuStrip->Items->Add(this->fileMenu);
			this->MainMenuStrip = this->menuStrip;

			this->gamesListBox = gcnew ListBox();
			this->gamesListBox->Location = System::Drawing::Point(10, 30);
			this->gamesListBox->Size = System::Drawing::Size(460, 150);
			this->gamesListBox->SelectedIndexChanged += gcnew EventHandler(this, &MyForm::GamesListBox_SelectedIndexChanged);

			this->titleTextBox = CreateTextBox(10, 200, titlePlaceholder);
			this->genreTextBox = CreateTextBox(10, 230, genrePlaceholder);
			this->releaseYearTextBox = CreateTextBox(10, 260, releaseYearPlaceholder);
			this->platformTextBox = CreateTextBox(10, 290, platformPlaceholder);
			this->developerTextBox = CreateTextBox(10, 320, developerPlaceholder);

			this->addButton = CreateButton("Add", 250, 200, gcnew EventHandler(this, &MyForm::AddButton_Click));
			this->updateButton = CreateButton("Update", 250, 230, gcnew EventHandler(this, &MyForm::UpdateButton_Click));
			this->deleteButton = CreateButton("Delete", 250, 260, gcnew EventHandler(this, &MyForm::DeleteButton_Click));

			this->aboutMenuItem->Click += gcnew EventHandler(this, &MyForm::AboutMenuItem_Click);
			this->exitMenuItem->Click += gcnew EventHandler(this, &MyForm::ExitMenuItem_Click);

			this->Controls->Add(this->gamesListBox);
			this->Controls->Add(this->titleTextBox);
			this->Controls->Add(this->genreTextBox);
			this->Controls->Add(this->releaseYearTextBox);
			this->Controls->Add(this->platformTextBox);
			this->Controls->Add(this->developerTextBox);
			this->Controls->Add(this->addButton);
			this->Controls->Add(this->updateButton);
			this->Controls->Add(this->deleteButton);
			this->Controls->Add(this->menuStrip);
		}

		TextBox^ CreateTextBox(int x, int y, String^ placeholder) {
			TextBox^ textBox = gcnew TextBox();
			textBox->Location = System::Drawing::Point(x, y);
			textBox->Text = placeholder;
			textBox->ForeColor = System::Drawing::Color::Gray;
			textBox->Enter += gcnew EventHandler(this, &MyForm::TextBox_Enter);
			textBox->Leave += gcnew EventHandler(this, &MyForm::TextBox_Leave);
			return textBox;
		}

		Button^ CreateButton(String^ text, int x, int y, EventHandler^ clickHandler) {
			Button^ button = gcnew Button();
			button->Text = text;
			button->Location = System::Drawing::Point(x, y);
			button->Click += clickHandler;
			return button;
		}
#pragma endregion

		void LoadData()
		{
			games = gcnew List<VideoGame^>(); 
			games->Add(gcnew VideoGame(nextId++, "Game A", "Action", 2020, "PC", "Dev A"));
			games->Add(gcnew VideoGame(nextId++, "Game B", "RPG", 2021, "Console", "Dev B"));
			games->Add(gcnew VideoGame(nextId++, "Game C", "Adventure", 2019, "PC", "Dev C"));

			UpdateGamesListBox();
		}

		void UpdateGamesListBox()
		{
			gamesListBox->Items->Clear();
			for each (VideoGame ^ game in games) {
				gamesListBox->Items->Add(game->ToString());
			}
		}

		void GamesListBox_SelectedIndexChanged(Object^ sender, EventArgs^ e)
		{
			int selectedIndex = gamesListBox->SelectedIndex;
			if (selectedIndex >= 0 && selectedIndex < games->Count) {
				VideoGame^ selectedGame = games[selectedIndex];
				titleTextBox->Text = selectedGame->title;
				genreTextBox->Text = selectedGame->genre;
				releaseYearTextBox->Text = selectedGame->releaseYear.ToString();
				platformTextBox->Text = selectedGame->platform;
				developerTextBox->Text = selectedGame->developer;
			}
		}

		void AddButton_Click(Object^ sender, EventArgs^ e)
		{
			VideoGame^ newGame = gcnew VideoGame(nextId++, titleTextBox->Text, genreTextBox->Text,
				Int32::Parse(releaseYearTextBox->Text), platformTextBox->Text, developerTextBox->Text);
			games->Add(newGame);
			UpdateGamesListBox();
		}

		void UpdateButton_Click(Object^ sender, EventArgs^ e)
		{
			int selectedIndex = gamesListBox->SelectedIndex;
			if (selectedIndex >= 0 && selectedIndex < games->Count) {
				games[selectedIndex]->title = titleTextBox->Text;
				games[selectedIndex]->genre = genreTextBox->Text;
				games[selectedIndex]->releaseYear = Int32::Parse(releaseYearTextBox->Text);
				games[selectedIndex]->platform = platformTextBox->Text;
				games[selectedIndex]->developer = developerTextBox->Text;
				UpdateGamesListBox();
			}
		}

		void DeleteButton_Click(Object^ sender, EventArgs^ e)
		{
			int selectedIndex = gamesListBox->SelectedIndex;
			if (selectedIndex >= 0 && selectedIndex < games->Count) {
				games->RemoveAt(selectedIndex);
				UpdateGamesListBox();
			}
		}

		void AboutMenuItem_Click(Object^ sender, EventArgs^ e)
		{
			MessageBox::Show("Video Game Catalog System\nVersion 1.0", "About");
		}

		void ExitMenuItem_Click(Object^ sender, EventArgs^ e)
		{
			this->Close();
		}

		void TextBox_Enter(Object^ sender, EventArgs^ e) {
			TextBox^ textBox = dynamic_cast<TextBox^>(sender);
			if (textBox->Text == titlePlaceholder || textBox->Text == genrePlaceholder ||
				textBox->Text == releaseYearPlaceholder || textBox->Text == platformPlaceholder ||
				textBox->Text == developerPlaceholder) {
				textBox->Text = "";
				textBox->ForeColor = System::Drawing::Color::Black;
			}
		}

		void TextBox_Leave(Object^ sender, EventArgs^ e) {
			TextBox^ textBox = dynamic_cast<TextBox^>(sender);
			if (textBox->Text == "") {
				if (textBox == titleTextBox) {
					textBox->Text = titlePlaceholder;
				}
				else if (textBox == genreTextBox) {
					textBox->Text = genrePlaceholder;
				}
				else if (textBox == releaseYearTextBox) {
					textBox->Text = releaseYearPlaceholder;
				}
				else if (textBox == platformTextBox) {
					textBox->Text = platformPlaceholder;
				}
				else if (textBox == developerTextBox) {
					textBox->Text = developerPlaceholder;
				}
				textBox->ForeColor = System::Drawing::Color::Gray;
			}
		}
	};
}
