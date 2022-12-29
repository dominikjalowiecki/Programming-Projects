/*
    Program analyses file consisting of letters:
    "a" - aceleration, "b" - break,  "l" - left turn,  "r" - right turn
    and outputs results in form of txt and xml files.
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>

using namespace std;

class RideReport
{
public:
  RideReport(const char *fileName);
  ~RideReport();
  bool readData();
  bool processData();
  int getSpeedUpCount();
  int getSlowDownCount();
  int getLeftTurnCount();
  int getRightTurnCount();
  void showReport();
  bool saveCleanedData(const char *fileName);
  bool saveAsText(const char *fileName);
  bool saveAsXML(const char *fileName);
private:
    char* fileName = NULL;
    char* buffer = NULL;
    int acceler = -1, slowd = -1, lturns = -1, rturns = -1;
};

RideReport::RideReport(const char *fileName)
{
    if(fileName != NULL)
    {
        size_t n = strlen(fileName) + 1;
        this->fileName = new char[n];
        strcpy(this->fileName, fileName);
    }
}

RideReport::~RideReport()
{
    delete[] fileName;
    fileName = NULL;

    delete[] buffer;
    buffer = NULL;
}

bool RideReport::readData()
{
    FILE * f = fopen(fileName, "rb");
    if(f != NULL)
    {
        fseek(f, 0, SEEK_END);
        long n = ftell(f) + 1;
        fseek(f, 0, SEEK_SET);

        try {
            buffer = new char[n];
        } catch(bad_alloc & e)
        {
            return false;
        }

        if(fread(buffer, sizeof(fileName[0]), n, f) != n - 1)
        {
            return false;
        }

        buffer[n-1] = '\0';

        fclose(f);
        f = NULL;

        return true;
    } else
    {
        return false;
    }
}

bool RideReport::processData()
{
    if(buffer == NULL) return false;

    acceler = slowd = lturns = rturns = 0;

    for(char* el = buffer; *el != '\0'; el++)
    {
        switch(tolower(*el))
        {
            case 'a':
                ++acceler;
                break;
            case 'b':
                ++slowd;
                break;
            case 'l':
                ++lturns;
                break;
            case 'r':
                ++rturns;
                break;
        }
    }

    return true;
}

int RideReport::getSpeedUpCount()
{
    return acceler;
}

int RideReport::getSlowDownCount()
{
    return slowd;
}

int RideReport::getLeftTurnCount()
{
    return lturns;
}

int RideReport::getRightTurnCount()
{
    return rturns;
}

void RideReport::showReport()
{
    if(buffer == NULL) return;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    printf("\n\n=== PODGLAD RAPORTU === \n");
    printf("Raport dla pliku: %s\n", this->fileName);
    printf("Data utworzenia: %4d-%02d-%02d\n", (1900 + ltm->tm_year), (1 + ltm->tm_mon), ltm->tm_mday);
    printf("Czas utworzenia: %02d:%02d:%02d\n", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    printf("Przyspieszenia: %d\n", acceler);
    printf("Hamowania: %d\n", slowd);
    printf("Lewo: %d\n", lturns);
    printf("Prawo: %d\n", rturns);
}

bool RideReport::saveCleanedData(const char *fileName)
{
    if(buffer == NULL) return false;

    FILE * f = fopen(fileName, "wt");
    if(f != NULL)
    {
        for(char* el = buffer; *el != '\0'; el++)
        {
            char le = tolower(*el);
            if(le == 'a' || le == 'b' || le == 'l' || le == 'r')
            {
                if(fputc(le, f) == EOF)
                {
                    return false;
                }
            }
        }

        fclose(f);
        f = NULL;

        return true;
    } else
    {
        return false;
    }
}

bool RideReport::saveAsText(const char *fileName)
{
    if(buffer == NULL) return false;

    FILE * f = fopen(fileName, "wt");
    if(f != NULL)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        fprintf(f, "Raport dla pliku: %s\n", this->fileName);
        fprintf(f, "Data utworzenia: %4d-%02d-%02d\n", (1900 + ltm->tm_year), (1 + ltm->tm_mon), ltm->tm_mday);
        fprintf(f, "Czas utworzenia: %02d:%02d:%02d\n", ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        fprintf(f, "Przyspieszenia: %d\n", acceler);
        fprintf(f, "Hamowania: %d\n", slowd);
        fprintf(f, "Lewo: %d\n", lturns);
        fprintf(f, "Prawo: %d", rturns);

        if(ferror(f))
        {
            return false;
        }

        fclose(f);
        f = NULL;

        return true;
    } else
    {
        return false;
    }
}

bool RideReport::saveAsXML(const char *fileName)
{
    if(buffer == NULL) return false;

    FILE * f = fopen(fileName, "wt");
    if(f != NULL)
    {

        time_t now = time(0);
        tm *ltm = localtime(&now);

        fprintf(f, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
        fprintf(f, "<report file=\"%s\" date=\"%4d-%02d-%02d\" time=\"%02d:%02d:%02d\">\n", this->fileName, (1900 + ltm->tm_year), (1 + ltm->tm_mon), ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
        fprintf(f, "<speed-up-count>%d</speed-up-count>\n", acceler);
        fprintf(f, "<slow-down-count>%d</slow-down-count>\n", slowd);
        fprintf(f, "<left-turn-count>%d</left-turn-count>\n", lturns);
        fprintf(f, "<right-turn-count>%d</right-turn-count>\n", rturns);
        fprintf(f, "</report>");

        if(ferror(f))
        {
            return false;
        }

        fclose(f);
        f = NULL;

        return true;
    } else
    {
        return false;
    }
}

void testTemplate(const char *inputFileName);

int main()
{
    RideReport report("dane.txt");
    if(report.readData())
    {
        if(report.processData())
        {
            cout << "\nPrzyspieszenia: " << report.getSpeedUpCount();
            cout << "\nHamowania: " << report.getSlowDownCount();
            cout << "\nW lewo: " << report.getLeftTurnCount();
            cout << "\nW prawo: " << report.getRightTurnCount();
            report.showReport();
            if(report.saveCleanedData("dane_czyste.txt"))
                cout << "\nOczyszczone dane zapisane";
            if(report.saveAsText("raport.txt"))
                cout << "\nRaport tekstowy zapisany";
            if(report.saveAsXML("raport.xml"))
                cout << "\nPlik XML zapisany";
        }
    }

    return EXIT_SUCCESS;
}
