#include<bits/stdc++.h>
#include <fstream>
#include "jagpdf-1.4.0.win32.x86.c_cpp\include\jagpdf\api.h"

#include <iostream>
#include <string.h>
#include <string>

using namespace std;
using namespace jag;

bool verificaInfo(string info, char pesquisa[]){
    char erro[5];
    strcpy(erro, info.c_str());
    if(strcmp(erro, pesquisa) == 0) return true;
    else return false;
}
string pegaData(string line){
    int i;
    char data[15];
    for(i = 0 ; i < 10 ; i++)
    {
        data[i] = line[line.length()-37+i] ;
    }
    data[i] = '\0';
    return data;
}
string pegaErro(string str){
    int i;
    char erro[5];
    for(i=0; i<3 ; i++)
    {
        erro[i] = str[i];
    }
    erro[i] = '\0';
    return erro;
}

int main(){
    FILE *arq = fopen("cabecalho.txt", "a+");
    FILE *arq1 = fopen("C:\\Users\\Ayrton Cossuol\\Desktop\\Novo_Trabalho\\dataset.dat", "a+");

    int operacao=-1;
    while(operacao!=0){
        printf("|-----------------------------------------------------|\n");
        printf("|                    MENU DE OPCOES                   |\n");
        printf("|-----------------------------------------------------|\n");
        printf("|--- 1 - IMPRIMIR RELATORIO DE ERROS NO TERMINAL. ----|\n");
        printf("|--- 2 - GERAR PDF DE RELATORIO DE ERROS. ------------|\n");
        printf("|--- 3 - FILTRAR POR CODIGO DE ERRO. -----------------|\n");
        printf("|--- 4 - FILTRAR POR DATA. ---------------------------|\n");
        printf("|--- 0 - SAIR. ---------------------------------------|\n");
        printf("|-----------------------------------------------------|\n");
        cout << endl;
        cout << "- Insira a sua OPCAO: ";
        cin >> operacao;
        if (operacao <0 || operacao >3){
            printf("---------------- PROGRAMA ENCERRADO! ----------------\n");
        }
        //************************* COPIA ARQUIVO ******************************
        ifstream ifs("dataset.dat");
        ofstream ofs("dataset.txt", ios::trunc);
        string data;
        while(!ifs.fail()){
            getline(ifs, data);
            ofs << data <<endl;
        }
        ifs.close();

        //**********************************************************************
        if(operacao == 1){
            char h;
            cout << endl;
            while((h=getc(arq1)) != EOF){
                printf("%c", h);
            }
            cout << "----------- FIM DO RELATORIO -----------"<< endl;
            system("pause");
            system("cls");
        }else if(operacao==2){
            char c,d[100],a[3000], traco[113];
            string e;
            int i=0, t=1000, b=1000, j=0, tf=0;
            for (int k=0; k<=100; ++k){
                d[k] = '\0';
            }
            pdf::Document doc(pdf::create_file("LogErro.pdf"));
            doc.page_start(568.7, 1000);
            cout << endl;

            for(i = 0 ; i < 112 ; i++){
                traco[i] = '-';
            }
            traco[i] = '\0';

            i=0;
            t-=12;
            doc.page().canvas().text_start(50,t);
            doc.page().canvas().text(traco);
            doc.page().canvas().text_translate_line(0,-15);
            doc.page().canvas().text_end();

            t-=30;
            doc.page().canvas().text_start(160,t);
            doc.page().canvas().text("RELATORIO GERAL DE ERROS");
            doc.page().canvas().text_translate_line(0,-15);
            doc.page().canvas().text_end();

            t-=40;
            doc.page().canvas().text_start(70,t);
            doc.page().canvas().text("ALUNOS: Ayrton Cossuol, Luan Frinhani, Thania Gomes, Wallace Carvalho");
            doc.page().canvas().text_translate_line(0,-15);
            doc.page().canvas().text_end();

            t-=20;
            doc.page().canvas().text_start(70,t);
            doc.page().canvas().text("PROFESSOR: Dr. Francisco de Assis Souza dos Santos");
            doc.page().canvas().text_translate_line(0,-15);
            doc.page().canvas().text_end();

            t-=10;
            doc.page().canvas().text_start(50,t);
            doc.page().canvas().text(traco);
            doc.page().canvas().text_translate_line(0,-15);
            doc.page().canvas().text_end();

            while((c=getc(arq1)) != EOF){
                d[i]=c;

                if(d[i]=='\n'){
                    if(t!=0){
                        t-=12;
                        doc.page().canvas().text_start(50,t);
                        doc.page().canvas().text(traco);
                        doc.page().canvas().text_translate_line(0,-15);
                        doc.page().canvas().text_end();

                        t-=12;
                        doc.page().canvas().text_start(50,t);
                        doc.page().canvas().text(d);
                        doc.page().canvas().text_translate_line(0,-15);
                        doc.page().canvas().text_end();
                        while(j<=i){
                            d[j]=' ';
                            j++;
                        }
                        i=0;
                        j=0;
                    }
                }
                i++;
            }

            t-=10;
            doc.page().canvas().text_start(50,t);
            doc.page().canvas().text(traco);
            doc.page().canvas().text_translate_line(0,-15);
            doc.page().canvas().text_end();

            doc.page_end();
            doc.finalize();

            fclose(arq);
            cout << "************************************"<<endl;
            cout << "--> O PDF FOI GERADO COM SUCESSO <--"<< endl;
            cout << "************************************"<<endl<< endl;

            cout << "ARQUIVO: LogErro.pdf"<<endl<<endl;
            system("pause");
            system("cls");
            //cout << "----------- PROGRAMA ENCERRADO! -----------"<< endl;
        }
        else if (operacao == 3){
            char pesquisa[10], traco[113];
            int i, t = 1000;

            for(i = 0 ; i < 112 ; i++){
                traco[i] = '-';
            }
            traco[i] = '\0';

            cout<< "DIGITE O CODIGO DO ERRO: ";
            cin>> pesquisa;
            string line, erro;
            ifstream myfile ("C:\\Users\\Ayrton Cossuol\\Desktop\\Novo_Trabalho\\dataset.dat");
            pdf::Document doc(pdf::create_file("LogSelecaoErro.pdf"));
            doc.page_start(597.6, 1000);//TAMANHO DA PÁGINA

            if (myfile.is_open()){
                t-=12;
                doc.page().canvas().text_start(50,t);
                doc.page().canvas().text(traco);
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=30;
                doc.page().canvas().text_start(160,t);
                doc.page().canvas().text("RELATORIO PELA SELECAO DO ERRO");
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=40;
                doc.page().canvas().text_start(70,t);
                doc.page().canvas().text("ALUNOS: Ayrton Cossuol, Luan Frinhani, Thania Gomes, Wallace Carvalho");
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=20;
                doc.page().canvas().text_start(70,t);
                doc.page().canvas().text("PROFESSOR: Dr. Francisco de Assis Souza dos Santos");
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=10;
                doc.page().canvas().text_start(50,t);
                doc.page().canvas().text(traco);
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                while (! myfile.eof() ){
                    getline (myfile,line);
                    erro = pegaErro(line);

                    if(verificaInfo(erro, pesquisa) == 1){
                        if (t!=0){
                            t-=12;
                            doc.page().canvas().text_start(50,t);
                            doc.page().canvas().text(traco);
                            doc.page().canvas().text_translate_line(0,-15);
                            doc.page().canvas().text_end();

                            t-=12;
                            doc.page().canvas().text_start(50,t);
                            doc.page().canvas().text(line.c_str());
                            doc.page().canvas().text_translate_line(0,-15);
                            doc.page().canvas().text_end();
                        }
                    }
                }

                t-=10;
                doc.page().canvas().text_start(50,t);
                doc.page().canvas().text(traco);
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();
                myfile.close();
            }

            doc.page_end();
            doc.finalize();
            cout << "************************************"<<endl;
            cout << "--> O PDF FOI GERADO COM SUCESSO <--"<< endl;
            cout << "************************************"<<endl<< endl;
            cout << "ARQUIVO: LogSelecaoErro.pdf"<<endl<<endl;
            system("pause");
            system("cls");
        }
        else if(operacao == 4){
            char pesquisa[20], traco[113];
            int t = 1000, i;

            for(i = 0 ; i < 112 ; i++){
                traco[i] = '-';
            }
            traco[i] = '\0';

            cout<< "DIGITE A DATA: (DD/MM/AAAA)";
            cin>> pesquisa;
            string line, data;
            ifstream myfile ("C:\\Users\\Ayrton Cossuol\\Desktop\\Novo_Trabalho\\dataset.dat");
            pdf::Document doc(pdf::create_file("LogSelecaoErro.pdf"));
            doc.page_start(597.6, 1000);//TAMANHO DA PÁGINA

            if (myfile.is_open()){
                t-=12;
                doc.page().canvas().text_start(50,t);
                doc.page().canvas().text(traco);
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=30;
                doc.page().canvas().text_start(160,t);
                doc.page().canvas().text("RELATORIO DA SELECAO DE ERROS POR DATA");
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=40;
                doc.page().canvas().text_start(70,t);
                doc.page().canvas().text("ALUNOS: Ayrton Cossuol, Luan Frinhani, Thania Gomes, Wallace Carvalho");
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=20;
                doc.page().canvas().text_start(70,t);
                doc.page().canvas().text("PROFESSOR: Dr. Francisco de Assis Souza dos Santos");
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                t-=10;
                doc.page().canvas().text_start(50,t);
                doc.page().canvas().text(traco);
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();

                while (! myfile.eof() ){
                    getline (myfile,line);
                    data = pegaData(line);
                    if(verificaInfo(data, pesquisa) == 1){
                        if (t!=0){
                            t-=12;
                            doc.page().canvas().text_start(50,t);
                            doc.page().canvas().text(traco);
                            doc.page().canvas().text_translate_line(0,-15);
                            doc.page().canvas().text_end();

                            t-=12;
                            doc.page().canvas().text_start(50,t);
                            doc.page().canvas().text(line.c_str());
                            doc.page().canvas().text_translate_line(0,-15);
                            doc.page().canvas().text_end();
                        }
                    }
                }

                t-=10;
                doc.page().canvas().text_start(50,t);
                doc.page().canvas().text(traco);
                doc.page().canvas().text_translate_line(0,-15);
                doc.page().canvas().text_end();
                myfile.close();
            }

            doc.page_end();
            doc.finalize();
            cout << "************************************"<<endl;
            cout << "--> O PDF FOI GERADO COM SUCESSO <--"<< endl;
            cout << "************************************"<<endl<< endl;
            cout << "ARQUIVO: LogSelecaoErro.pdf"<<endl<<endl;
            system("pause");
            system("cls");
        }
        else if (operacao == 0){
            cout << "----------- PROGRAMA ENCERRADO! -----------"<< endl;
            break;
        }
    }
    return 0;
}
