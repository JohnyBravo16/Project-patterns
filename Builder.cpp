#include <iostream>
#include <string>
#include <locale>

using namespace std;

class TextConverter;
class ASCIIConverter;
class TeXConverter;
class TextWidgetConverter;
class Product;
class AsciiText;
class TexText;
class WidgetText;
class RTFReader;


class TextConverter
{
 public:
    TextConverter()
    {
        product = 0;
    };
    virtual Product* ConvertCharacter(string) = 0;
    virtual Product* ConvertCharacterRemove(string){};
    //virtual void GetProduct() = 0;
 protected:
    Product* product;
};

class ASCIIConverter : public TextConverter
{
 public:
    ASCIIConverter();
    Product* ConvertCharacter(string);
    string RemoveSubString(string, string);
    string GetASCIIText();
 private:
    string text;
};

class TeXConverter : public TextConverter
{
 public:
    TeXConverter();
    Product* ConvertCharacter(string);
    Product* ConvertCharacterRemove(string);
    string ConvertMarkers(string, string);
    string GetTeXText();
    string ToUpperAndRemove(string, string, string);
    string ToUpperNoRemove(string, string, string);
    string Upper(string);
 private:
    string text;
};

class TextWidgetConverter : public TextConverter
{
 public:
    TextWidgetConverter();
    Product* ConvertCharacter(string);
    string ConvertToMarker(string, string, string);
    string GetTextWidget();
    string ConvertMarker(string, string, string);
 private:
    string text;
};

class Product
{
 public:
    Product(string text)
    {
        this->text = text;
    }
    //virtual Product* SetProduct(string) = 0;
    virtual void GetProduct()
    {
        cout<<this->text<<endl;
    }
 protected:
    string text;
};

class AsciiText : public Product
{
 public:
    AsciiText(string text) : Product(text){};
};

class TexText : public Product
{
 public:
    TexText(string text) : Product(text){};
};

class WidgetText : public Product
{
 public:
    WidgetText(string text) : Product(text){};
};

class RTFReader
{
 private:
    TextConverter* tc;
 public:
    RTFReader() : tc(0)
    {

    }
    ~RTFReader()
    {
        if(tc)
            delete tc;
    }
    void ParseRTF(TextConverter* tec)
    {
        if(this->tc)
            delete this->tc;
        this->tc = tec;    
    }
    Product* Construct(string text, string method = "")
    {
        Product* prod;
        if(method == "withRemove")
        {
            prod = tc->ConvertCharacterRemove(text);
            prod->GetProduct();
        }
        else
        {
            prod = tc->ConvertCharacter(text);
            
        }
        prod->GetProduct();
        
        return prod;
    }
};

ASCIIConverter::ASCIIConverter()
{
    text = "";
}

Product* ASCIIConverter::ConvertCharacter(string text)
{
    string converted_text = text;

    converted_text = RemoveSubString(text, "<b>");
    converted_text = RemoveSubString(converted_text, "</b>");
    converted_text = RemoveSubString(converted_text, "<i>");
    converted_text = RemoveSubString(converted_text, "</i>");
    converted_text = RemoveSubString(converted_text, "<u>");
    converted_text = RemoveSubString(converted_text, "</u>");

    Product* temp = new AsciiText(converted_text);

    return temp;
}

string ASCIIConverter::RemoveSubString(string text, string subText)
{
    string converted_text = text;

    size_t pos = converted_text.find(subText);
    string temp = "";

    while( pos != string::npos)
	{
		converted_text.replace(pos, subText.size(), temp);
		pos = converted_text.find(subText, pos + temp.size());
	}
    return converted_text;
}

string ASCIIConverter::GetASCIIText()
{
    return text;
}

TeXConverter::TeXConverter()
{
    text = "";
}

Product* TeXConverter::ConvertCharacterRemove(string text)
{
    string converted_text = text;

    converted_text = ConvertMarkers(converted_text, "Remove");

    Product* prod = new TexText(converted_text);

    return prod;
}

Product* TeXConverter::ConvertCharacter(string text)
{
    string converted_text = text;

    converted_text = ConvertMarkers(converted_text, "NoRemove");

    Product* prod = new TexText(converted_text);

    return prod;
}

string TeXConverter::ConvertMarkers(string text, string method)
{
    string converted_text = text;

    if(method == "Remove")
    {
        converted_text = ToUpperAndRemove(text, "<b>", "</b>");
        converted_text = ToUpperAndRemove(converted_text, "<i>", "</i>");
        converted_text = ToUpperAndRemove(converted_text, "<u>", "</u>");
    }
    if(method == "NoRemove")
    {
        converted_text = ToUpperNoRemove(text, "<b>", "</b>");
        converted_text = ToUpperNoRemove(converted_text, "<i>", "</i>");
        converted_text = ToUpperNoRemove(converted_text, "<u>", "</u>");
    }

    return converted_text;
}

string TeXConverter::ToUpperAndRemove(string text, string marker1, string marker2)
{
    string converted_text = text;
    string temp;

    ASCIIConverter ac;

    size_t pos = converted_text.find(marker1);
    size_t pos2 = converted_text.find(marker2);

    while((pos != string::npos) && pos2 != string::npos)
	{
        temp = converted_text.substr(pos + 3, pos2 - pos - 3);

        //temp = ac.ConvertCharacter(temp);

        temp = Upper(temp);

        converted_text = ac.RemoveSubString(converted_text, marker1);
        converted_text = ac.RemoveSubString(converted_text, marker2);

        converted_text.replace(pos, temp.size(), temp);

        pos = converted_text.find(marker1, pos + marker2.size());
        pos2 = converted_text.find(marker2, pos2 + marker2.size());
	}
    return converted_text;
}

string TeXConverter::ToUpperNoRemove(string text, string marker1, string marker2)
{
    string converted_text = text;
    string temp;

    size_t pos = converted_text.find(marker1);
    size_t pos2 = converted_text.find(marker2);

    while((pos != string::npos) && pos2 != string::npos)
	{
        temp = converted_text.substr(pos + 3, pos2 - pos - 3);

        //temp = ac.ConvertCharacter(temp);

        temp = Upper(temp);

        converted_text.replace(pos + 3, temp.size(), temp);

        pos = converted_text.find(marker1, pos + marker2.size());
        pos2 = converted_text.find(marker2, pos2 + marker2.size());
	}
    return converted_text;
}

string TeXConverter::Upper(string text)
{
    string temp = text;

    locale loc;

    for(int i=0;i<temp.length();i++)
    {
        temp[i] = toupper(temp[i], loc);
    }
    return temp;
}

string TeXConverter::GetTeXText()
{
    return text;
}

TextWidgetConverter::TextWidgetConverter()
{
    this->text = "";
}

Product* TextWidgetConverter::ConvertCharacter(string text)
{
    string converted_text = text;

    converted_text = ConvertToMarker(converted_text, "<b>", "</b>");
    converted_text = ConvertToMarker(converted_text, "<u>", "</u>");
    converted_text = ConvertToMarker(converted_text, "<i>", "</i>");

    Product* prod = new WidgetText(converted_text);

    return prod;

 //   return converted_text;
}

string TextWidgetConverter::ConvertToMarker(string text, string marker1, string marker2)
{
    string converted_text = text;
    string temp;
    string marked_text;

    size_t pos = converted_text.find(marker1);
    size_t pos2 = converted_text.find(marker2);

    while((pos != string::npos) && pos2 != string::npos)
	{
        temp = converted_text.substr(pos, pos2 - pos + 4);

        marked_text = ConvertMarker(converted_text, marker1, marker2);
        //temp = ac.ConvertCharacter(temp);
        //temp = ConvertMarker(temp);
        
        cout<<temp<<endl;
        
        converted_text.replace(pos, marked_text.size() + 4, marked_text);
        
        pos = converted_text.find(marker1, pos + marker2.size());
        pos2 = converted_text.find(marker2, pos2 + marker2.size());
	}
    return converted_text;
}

string TextWidgetConverter::ConvertMarker(string text, string marker1, string marker2)
{
    string converted_text = text;
    string temp;
    string marked_text;

    size_t pos = converted_text.find(marker1);
    size_t pos2 = converted_text.find(marker2);

    while((pos != string::npos) && pos2 != string::npos)
	{
        temp = converted_text.substr(pos + 3, pos2 - pos - 3);

        if(marker1 == "<b>")
            marked_text = "{b#" + temp + "}";
        if(marker1 == "<u>")
            marked_text = "{u#" + temp + "}";
        if(marker1 == "<i>")
            marked_text = "{i#" + temp + "}";

        cout<<marked_text<<endl;

        pos = converted_text.find(marker1, pos + marker2.size());
        pos2 = converted_text.find(marker2, pos2 + marker2.size());
	}
    
    return marked_text;
}

string TextWidgetConverter::GetTextWidget()
{
    return text;
}

int main()
{   
    string textAscii = "Ala ma kota, Tomek ma psa.";
    string textFormattedAscii = "Al<b>a</b> <u>ma</u> kota, <i>Tomek</i> ma psa.";

    cout<<textFormattedAscii<<endl;

    ASCIIConverter* ac = new ASCIIConverter;
    //TeXConverter* tc = new TeXConverter;
    //TextWidgetConverter* tw = new TextWidgetConverter();
    RTFReader rtf;

    rtf.ParseRTF(ac);

    //rtf.Construct(textFormattedAscii, "withRemove");
    rtf.Construct(textFormattedAscii);

    return 0;
}