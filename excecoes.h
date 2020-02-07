// BIBLIOTECAS UTILIZADAS NO PROGRAMA
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <math.h>
#include <locale.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <Windows.h>

#define pulaLinha cout <<endl;
#define ZERO 000000000000000000000
using namespace std;

//****************** ESTRUTURA REFERENTE AS CORES USADAS NO PROGRAMA *******************************
enum DOS_COLORS{
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
    LIGHT_GRAY, DARK_GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN,
    LIGHT_RED, LIGHT_MAGENTA, YELLOW, WHITE
};

//-------------------------------------------------------------

void textcolor (DOS_COLORS iColor){
    HANDLE hl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    BOOL b = GetConsoleScreenBufferInfo(hl, &bufferInfo);
    bufferInfo.wAttributes &= 0x00F0;
    SetConsoleTextAttribute (hl, bufferInfo.wAttributes |= iColor);
}

//************************************************************************************************

//PROTOTIPOS UTILIZADDOS PARA LEITURA E ESCRITA DE ARQUIVO
bool escreveArquivo(ofstream&, char*);
bool leArquivo (ifstream&, char*);

bool status;
//ofstream outFile;
fstream outFile("dataset.dat",ios::in | ios::out | ios::app);

//bool flagLe = leArquivo(inputFile, "dataset.dat");

//bool flagEscreve = escreveArquivo(outFile, "dataset.dat");

//int codigoErro=1;

//******************** METODO PARA ESCREVER DATA E HORA NO ARQUIVO .dat ********************
void escreveData (){
    // DATA E TEMPO SAO BASEADOS NO SISTEMA
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout<<ltm->tm_hour;
    outFile <<"Data: " << ltm->tm_mday << "/" << 1 + ltm->tm_mon <<"/"<<1900 + ltm->tm_year;
    if (ltm->tm_hour < 10 && ltm->tm_min > 10 && ltm->tm_sec > 10){
        outFile<<"   |   Horario: 0"<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<ltm->tm_sec<<"  |"<<endl;
    }
    if (ltm->tm_hour < 10 && ltm->tm_min < 10 && ltm->tm_sec > 10){
        outFile<<"   |   Horario: 0"<<ltm->tm_hour<<":"<<"0"<<ltm->tm_min<<":"<<ltm->tm_sec<<"  |"<<endl;
    }
    if (ltm->tm_hour < 10 && ltm->tm_min > 10 && ltm->tm_sec < 10){
        outFile<<"   |   Horario: 0"<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<"0"<<ltm->tm_sec<<"  |"<<endl;
    }
    if (ltm->tm_hour < 10 && ltm->tm_min < 10 && ltm->tm_sec < 10){
        outFile<<"   |   Horario: 0"<<ltm->tm_hour<<":"<<"0"<<ltm->tm_min<<":"<<"0"<<ltm->tm_sec<<"  |"<<endl;
    }
    if (ltm->tm_hour > 10 && ltm->tm_min < 10 && ltm->tm_sec > 10){
        outFile<<"   |   Horario: "<<ltm->tm_hour<<":"<<"0"<<ltm->tm_min<<":"<<ltm->tm_sec<<"  |"<<endl;
    }
    if (ltm->tm_hour > 10 && ltm->tm_min < 10 && ltm->tm_sec < 10){
        outFile<<"   |   Horario: "<<ltm->tm_hour<<":"<<"0"<<ltm->tm_min<<":"<<"0"<<ltm->tm_sec<<"  |"<<endl;
    }
    if (ltm->tm_hour > 10 && ltm->tm_min > 10 && ltm->tm_sec > 10){
        outFile<<"   |   Horario: "<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<ltm->tm_sec<<"  |"<<endl;
    }

    outFile.precision(2);
}
//********************************************************************************************

template <class T> class excecoes{

public:
    class erro { }; /*classe para referência na ocorrencia de erro. Utiliza-se construtor por ocultação*/
    void Mensagem(string msg); /*Permite passar por parâmetro qualquer mensagem e exibi-la para o usuário*/
    bool isDivByZero(T numero); /*retorna true se ocorreu uma tentativa de divisao por zero*/
    bool isNegativeSQR(T numero); /*retorna true se houver tentativa de raiz negativa */
    bool isNumber (T numero); /*retorna true se o valor valor passado possui apenas números */
    bool isWord (T palavra); /*retorna true se o valor valor passado possui apenas char */
    bool isDate (T dia, T mes, T ano); /*returna true se for uma data válida */
    T *alocation(T *ptr); /*Caso não ocorra um erro de alocação de memmória devolve um ponteriro alocado */
    bool isIndexInvalid(T vetor[], int i);
    bool redimencionar(T tam);
    T *alocarChar(T tam);
    bool AtribuiValorVetor(T tam, std::vector<int>Vetor, T pos, T valor);
    //....demais métodos para tratamento de erros

private:
    T item; /*Atributo privado que futuramente pode ser utilizado*/
};



template <class T> void excecoes<T>:: Mensagem(string msg) /*implementação do método mensagem */
{
    cout << msg << endl;
}
///////////////////////////////////////////////////////////////////
template <class T> bool excecoes<T>::isDivByZero(T numero)  /*implementação da verificação de tentativa de divisao por zero */
{
    try{
        if (numero==ZERO){
            throw (erro());
        }
        else{
            return true;
        }
    } // final do bloco TRY
    catch (excecoes::erro){
        textcolor(RED);
        Mensagem("\nERRO: Divisao por zero\n");
        textcolor(WHITE);
        pulaLinha;
        outFile<<"000 ERRO | Divisao por Zero                 |  ";
        escreveData(); //Escreve Dia/Mes/Ano e Hora:Minuto:Segundo no arquivo.dat
        return false;
    }
}

template <class T> bool excecoes<T>::isNegativeSQR(T numero)  /*implementação da verificação de tentativa de divisao por zero */
{
    try{
        if (numero < (double)ZERO){
            throw (erro());
            //return true;
        }
        else{
            return true;
        }

    } // final do bloco TRY
    catch (excecoes::erro){
        textcolor(RED);
        Mensagem("\nERRO: Raiz Negativa\n");
        textcolor(WHITE);
        pulaLinha;
        outFile<<"101 ERRO | Raiz Negativa                    |  ";
        escreveData(); //Escreve Dia/Mes/Ano e Hora:Minuto:Segundo no arquivo.dat
        return false;
    }
}

template <class T> bool excecoes<T>::isNumber (T numero)
{
    int cont=0;
    for (int i=0; i<numero.length(); ++i){
        if(numero[i]>=48 && numero[i]<=57){
            cont++;
        }
    }
    try{
        if (cont != numero.length()){
            throw (erro());
        }
        else if (cont == numero.length()){
            return true;
        }

    }
    catch (excecoes::erro){
        textcolor(RED);
        Mensagem("\nERRO: O dado inserido nao e um numero\n");
        textcolor(WHITE);
        pulaLinha;
        outFile<<"202 ERRO | Dado nao e um numero     |  ";
        escreveData(); //Escreve Dia/Mes/Ano e Hora:Minuto:Segundo no arquivo.dat
        return false;
    }
}

template <class T> bool excecoes<T>::isWord (T numero)
{
    int cont=0;
    for (int i=0; i<numero.length(); ++i){
        if((numero[i]>=65 && numero[i]<=90)||(numero[i]>=97 && numero[i]<=122)){
            cont++;
        }
    }
    try{
        if (cont != numero.length()){
            throw (erro());
        }
        else
            return true;
    } // final do bloco TRY
    catch (excecoes::erro){
        textcolor(RED);
        Mensagem("\nERRO: O dado inserido nao e uma letra\n");
        textcolor(WHITE);
        pulaLinha;
        outFile<<"303 ERRO | Dado nao e uma letra        |  ";
        escreveData(); //Escreve Dia/Mes/Ano e Hora:Minuto:Segundo no arquivo.dat
        return false;
    }
}

template <class T> bool excecoes<T>::isDate (T dia, T mes, T ano)
{
    //int verifica=0;

    try{
        if (mes>12){
            throw(erro());
            return false;
        }
        else if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || 12) && dia>31){
            throw(erro());
            return false;
        }
        else if ((mes==4 || mes==6 || mes==9 || mes==11) && dia>30){
            throw(erro());
            return false;
        }
        else if (mes==2 && dia>28){
            throw(erro());
            return false;
        }
        else
            return true;
    }
    catch(excecoes::erro){
        textcolor(RED);
        Mensagem("\nERRO: Dado inserido nao e uma data aceitavel\n");
        textcolor(WHITE);
        pulaLinha;
        outFile<<"404 ERRO | Dado nao e uma data        |  ";
        escreveData(); //Escreve Dia/Mes/Ano e Hora:Minuto:Segundo no arquivo.dat
        return false;
    }
}

template <class T> T* excecoes<T>::alocation (T *ptr)
{
    try{
        if (ptr == NULL || *ptr == 0) throw(erro());

        else{
            ptr = new (nothrow) T;
            return ptr;
        }
    }
    catch(excecoes::erro){
        textcolor(RED);
        Mensagem("\nERRO: erro na alocacao de memoria\n");
        textcolor(WHITE);
        pulaLinha;
        outFile<<"505 ERRO | Erro alocacao de memoria |  ";
        escreveData(); //Escreve Dia/Mes/Ano e Hora:Minuto:Segundo no arquivo.dat
        return NULL;
    }
}

template <class T> bool excecoes<T>:: isIndexInvalid(T vetor[], int i)
{
    int tam = 8;
    try{
        if(i < 0){
            throw(erro());
        }
        if(i > tam){
            throw(erro());
        }
        else{
            return true;
        }
    }
    catch(excecoes::erro){
        textcolor(RED);
        Mensagem("\nERRO: index fora do limite do vetor\n");
        textcolor(WHITE);
        outFile<<"606 ERRO | Index fora do limite             |";
        escreveData();
        return false;
    }
}

template <class T>bool excecoes<T>::redimencionar(T tam)
{
    try{
        std::vector<int> myvector;
        myvector.resize(tam);
        return true;
    }
    catch(const std::length_error& le){
        textcolor(RED);
        Mensagem("\nERRO: erro de redimencionamento de vetor\n");
        textcolor(WHITE);
        outFile<<"707 ERRO | Erro ao redimensionar        |  ";
        escreveData();
        pulaLinha;
        return false;
    }
}
template <class T> T* excecoes<T>::alocarChar(T tam)
{
    char* p;
    while (tam!=0){
        try{
            p = new char [tam];
            return p;
        }
        catch (std::bad_alloc& e){
            outFile<<"808 ERRO | Erro de alocacao de char   |  ";
            escreveData();
            return p;
        }
    }
}
template <class T> bool excecoes<T>::AtribuiValorVetor(T tam, std::vector<int>Vetor, T pos, T valor)
{
    try{
        Vetor.at(pos) = valor;
        return true;
    }
    catch (const std::out_of_range& oor){
        textcolor(RED);
        Mensagem("\nERRO: erro de atribuicao no vetor\n");
        textcolor(WHITE);
        outFile<<"909 ERRO | Erro ao atribuir valor           |  ";
        escreveData();
        return false;
    }
}


// ******************* MANIPULACAO DE ARQUIVO ****************************
bool escreveArquivo (ofstream& file, char* strFile)  //ESCREVE NO ARQUIVO
{
    file.open(strFile);
    return !(file.fail()||!file.is_open()||!file.good());
}

bool leArquivo (ifstream& ifile, char* strFile) 	//LE O ARQUIVO
{
    ifile.open(strFile);
    return !(ifile.fail()||!ifile.is_open()||!ifile.good());
}

//***************************************************************************

