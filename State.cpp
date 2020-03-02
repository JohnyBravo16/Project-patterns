#include <iostream>

using namespace std;

class File;
class FileState;
class FileClosed;
class FileOpened;

class File
{
 public:
    File();
    void Open();
    void Close();
    void Read();
    void Write();
 private:
    friend class FileState;
    void ChangeState(FileState*);
    FileState* fs;
};

class FileState
{
 public:
    virtual void Open(File* f)
    {
        cout<<"Plik jest juz otwarty."<<endl;
    };
    virtual void Close(File* f)
    {
        cout<<"Plik jest juz zamkniety."<<endl;
    };
    virtual void Read(File* f)
    {
        cout<<"Nie mozna odczytac bez zaladowania pliku!"<<endl;
    };
    virtual void Write(File* f)
    {
        cout<<"Nie mozna zapisac bez zaladowania pliku!"<<endl;
    };
 protected:
    void ChangeState(File* c, FileState* s)
    {
        c->ChangeState(s);
    }
};

class FileClosed : public FileState
{
 public:
    void Open(File*);
};

class FileOpened : public FileState
{
 public:
    void Read(File*);
    void Write(File*);
    void Close(File*);
};

File::File()
{
    fs = new FileClosed;
}

void File::Open()
{
    fs->Open(this);
}

void File::Close()
{
    fs->Close(this);
}

void File::Read()
{
    fs->Read(this);
}

void File::Write()
{
    fs->Write(this);
}

void File::ChangeState(FileState* state)
{
    fs = state;
}

void FileClosed::Open(File* f)
{
    cout<<"[Otwieranie pliku..]"<<endl;
    ChangeState(f, new FileOpened);
    delete this;
}

void FileOpened::Read(File* f)
{
    cout<<"Odczytywanie pliku.."<<endl;
}

void FileOpened::Write(File* f)
{
    cout<<"Zapisywanie do pliku.."<<endl;
}

void FileOpened::Close(File* f)
{
    cout<<"[Zamykanie pliku..]"<<endl;
    ChangeState(f, new FileClosed);
    delete this;
}

int main()
{
    File* f = new File;

    f->Close();
    f->Open();
    f->Open();
    f->Read();
    f->Write();
    f->Close();
    f->Write();
    f->Read();
    

    return 0;
}