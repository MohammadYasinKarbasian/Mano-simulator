#include<QFileDialog>
#include<fstream>
#include<QFile>
#include<QMessageBox>
#include<QTableWidget>
#include<sstream>
#include <ctype.h>
#include "Mainwindow.h"
#include "ui_Mainwindow.h"

QString bitset8toQString(bitset<8> bits){
    QString str = "";
    if(bits[7]&&bits[6]&&bits[5]&&bits[4]){
        str += 'F';
    }
    else if(bits[7]&&bits[6]&&bits[5]&&!bits[4]){
        str += 'E';
    }
    else if(bits[7]&&bits[6]&&!bits[5]&&bits[4]){
        str += 'D';
    }
    else if(bits[7]&&bits[6]&&!bits[5]&&!bits[4]){
        str += 'C';
    }
    else if(bits[7]&&!bits[6]&&bits[5]&&bits[4]){
        str += 'B';
    }
    else if(bits[7]&&!bits[6]&&bits[5]&&!bits[4]){
        str += 'A';
    }
    else if(bits[7]&&!bits[6]&&!bits[5]&&bits[4]){
        str += '9';
    }
    else if(bits[7]&&!bits[6]&&!bits[5]&&!bits[4]){
        str += '8';
    }
    else if(!bits[7]&&bits[6]&&bits[5]&&bits[4]){
        str += '7';
    }
    else if(!bits[7]&&bits[6]&&bits[5]&&!bits[4]){
        str += '6';
    }
    else if(!bits[7]&&bits[6]&&!bits[5]&&bits[4]){
        str += '5';
    }
    else if(!bits[7]&&bits[6]&&!bits[5]&&!bits[4]){
        str += '4';
    }
    else if(!bits[7]&&!bits[6]&&bits[5]&&bits[4]){
        str += '3';
    }
    else if(!bits[7]&&!bits[6]&&bits[5]&&!bits[4]){
        str += '2';
    }
    else if(!bits[7]&&!bits[6]&&!bits[5]&&bits[4]){
        str += '1';
    }
    else if(!bits[7]&&!bits[6]&&!bits[5]&&!bits[4]){
        str += '0';
    }

    if(bits[3]&&bits[2]&&bits[1]&&bits[0]){
        str += 'F';
    }
    else if(bits[3]&&bits[2]&&bits[1]&&!bits[0]){
        str += 'E';
    }
    else if(bits[3]&&bits[2]&&!bits[1]&&bits[0]){
        str += 'D';
    }
    else if(bits[3]&&bits[2]&&!bits[1]&&!bits[0]){
        str += 'C';
    }
    else if(bits[3]&&!bits[2]&&bits[1]&&bits[0]){
        str += 'B';
    }
    else if(bits[3]&&!bits[2]&&bits[1]&&!bits[0]){
        str += 'A';
    }
    else if(bits[3]&&!bits[2]&&!bits[1]&&bits[0]){
        str += '9';
    }
    else if(bits[3]&&!bits[2]&&!bits[1]&&!bits[0]){
        str += '8';
    }
    else if(!bits[3]&&bits[2]&&bits[1]&&bits[0]){
        str += '7';
    }
    else if(!bits[3]&&bits[2]&&bits[1]&&!bits[0]){
        str += '6';
    }
    else if(!bits[3]&&bits[2]&&!bits[1]&&bits[0]){
        str += '5';
    }
    else if(!bits[3]&&bits[2]&&!bits[1]&&!bits[0]){
        str += '4';
    }
    else if(!bits[3]&&!bits[2]&&bits[1]&&bits[0]){
        str += '3';
    }
    else if(!bits[3]&&!bits[2]&&bits[1]&&!bits[0]){
        str += '2';
    }
    else if(!bits[3]&&!bits[2]&&!bits[1]&&bits[0]){
        str += '1';
    }
    else if(!bits[3]&&!bits[2]&&!bits[1]&&!bits[0]){
        str += '0';
    }
    return str;
}

bool MainWindow::isHex(const QString &str)
{

    string check=str.toStdString();
    for (char const &c : check)
    {
        if(c=='a' || c=='b' || c=='c' || c=='d' || c=='e' || c=='f'|| c=='A' || c=='B' || c=='C' || c=='D' || c=='E' || c=='F'|| c=='-' || c=='+')
        {
            continue;
        }
        if (isdigit(c) == 0) return false;
    }
       return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Output->setReadOnly(1);
    ui->CurrentOper->setReadOnly(1);
    ui->PC->setReadOnly(1);
    ui->AR->setReadOnly(1);
    ui->IR->setReadOnly(1);
    ui->DR->setReadOnly(1);
    ui->SC->setReadOnly(1);
    ui->AC->setReadOnly(1);
    ui->TR->setReadOnly(1);
    ui->INPR->setReadOnly(1);
    ui->OUTR->setReadOnly(1);
    ui->IEN->setReadOnly(1);
    ui->FGI->setReadOnly(1);
    ui->FGO->setReadOnly(1);
    ui->I->setReadOnly(1);
    ui->S->setReadOnly(1);
    ui->E->setReadOnly(1);
    ui->R->setReadOnly(1);
    ui->RAM->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_NEXT_clicked()
{
    if(!run)
    {
        printing=1;
    }
    if(!is_compiled)
    {
        ui->Output->setText("Before run, first you need to compile your code\n");
    }
    else
    {
        ui->RAM->selectRow(memorystep-1);
        ui->Output->clear();

                SC=clk;

                    QStringList commandLine = commands.at(lineStep).split(' ', Qt::SkipEmptyParts);
                    if(commandLine.at(0)=="ORG"){
                        bool ok=1;
                        memorystep=commandLine.at(1).toInt(&ok,16);
                        lineStep++;
                    }
                    commandLine = commands.at(lineStep).split(' ', Qt::SkipEmptyParts);


                    if(clk==0)
                    {
                        S=1;
                        PC=memorystep;
                        AR=PC;
                        clk++;
                        SC=clk;
                        if(printing)
                        {
                            printReg();
                            printTable();
                        }

                        ui->CurrentOper->setText("In T0: FETCH (AR <- PC)");
                        return;
                    }

                    else if(clk==1)
                    {
                        incrPC();
                        memorystep++;
                        IR=RAM[AR.to_ulong()];
                        clk++;
                        SC=clk;
                        if(printing)
                        {
                            printReg();
                            printTable();
                        }
                        ui->CurrentOper->setText("In T1: FETCH (PC <- PC+1 , IR <- M[AR]) ");
                        return;
                    }

                    else if(clk==2)
                    {
                        for (int bitC=0;bitC<12;bitC++)
                        {
                            AR[bitC]=IR[bitC];

                        }
                        I[0]=IR[15];
                        clk++;
                        ui->CurrentOper->setText("In T2: DECODE(AR <- IR(0-11) , I <- IR(15)) ");
                        return;
                    }

                    if(commandLine.at(0)[commandLine.at(0).size()-1]==',')
                    {

                            for(int x=0;x<(commandLine.length())-1;x++)
                            {
                                commandLine[x]=commandLine[x+1];
                            }

                    }
                    if(commandLine.at(0)=="DEC")
                    {
                        clk=0;
                        lineStep++;
                    }
                    else if(commandLine.at(0)=="HEX")
                    {
                        clk=0;
                        lineStep++;
                    }

                    else if(commandLine.at(0)=="AND")
                    {
                        if(clk==3)
                        {

                            clk++;
                            if(commandLine.size()>=3 && commandLine.at(2)=='I')
                            {
                                ui->CurrentOper->setText("AR <- M[AR] ");
                                int tmpAR=AR.to_ulong();
                                for (int bitC=0;bitC<12;bitC++)
                                {
                                    AR[bitC]=RAM[tmpAR][bitC];
                                }
                            }
                        }

                        else if (clk==4) {
                            ui->CurrentOper->setText("DR <- M[AR]");
                            clk++;
                            DR=RAM[AR.to_ulong()];
                        }
                        else if (clk==5) {
                            clk=0;
                            SC=0;
                            lineStep++;
                            AC = AC & DR;
                            ui->CurrentOper->setText("AC <- AC&DR  , SC <- 0");
                        }
                    }
                    else if(commandLine.at(0)=="ADD")
                    {
                        if(clk==3)
                        {
                            clk++;
                            if(commandLine.size()>=3 && commandLine.at(2)=='I')
                            {
                                ui->CurrentOper->setText("AR <- M[AR] ");
                                bitset<12> tmpAR=AR;
                                for (int bitC=0;bitC<12;bitC++)
                                {
                                    AR[bitC]=RAM[tmpAR.to_ulong()][bitC];
                                }
                            }
                            else
                            {}
                        }
                        if(clk==4)
                        {
                            clk++;
                            DR=RAM[AR.to_ulong()];
                            ui->CurrentOper->setText("DR <- M[AR]");
                        }
                        if(clk==5)
                        {
                            clk=0;
                            lineStep++;
                            SC=0;
                            std::bitset<1> TempCout(0);
                            std::bitset<16> TempSum(0);

                            for(quint16 i = 0; i < AC.size(); i++){
                                TempSum[i] = AC[i] ^ DR[i] ^ TempCout[0];
                                TempCout = (TempCout[0] & (AC[i] ^ DR[i])) | (AC[i] & DR[i]);
                            }

                            E = TempCout;
                            AC = TempSum;

                            ui->CurrentOper->setText(" AC <- AC+DR , E<-COUT , SC <- 0");
                        }
                    }
                    else if(commandLine.at(0)=="LDA")
                    {
                        if(clk==3)
                        {
                            clk++;
                            if(commandLine.size()>=3 && commandLine.at(2)=='I')
                            {
                                ui->CurrentOper->setText("AR <- M[AR] ");
                                bitset<12> tmpAR=AR;
                                for (int bitC=0;bitC<12;bitC++)
                                {
                                    AR[bitC]=RAM[tmpAR.to_ulong()][bitC];
                                }
                            }
                        }
                        else if(clk==4)
                        {
                            clk++;
                            DR=RAM[AR.to_ulong()];
                            ui->CurrentOper->setText("DR <- M[AR]");
                        }
                        else if (clk==5) {
                            SC=0;
                            clk=0;
                            lineStep++;
                            AC=DR;
                            ui->CurrentOper->setText("AC <- DR , SC <- 0");
                        }
                    }
                    else if(commandLine.at(0)=="STA")
                    {
                        if(clk==3)
                        {
                            clk++;
                            if(commandLine.size()>=3 && commandLine.at(2)=='I')
                            {
                                ui->CurrentOper->setText("AR <- M[AR] ");
                                bitset<12> tmpAR=AR;
                                for (int bitC=0;bitC<12;bitC++)
                                {
                                    AR[bitC]=RAM[tmpAR.to_ulong()][bitC];
                                }
                            }
                        }
                        else if(clk==4)
                        {
                            ui->CurrentOper->setText("M[AR] <- AC , SC <- 0");
                            SC=0;
                            lineStep++;
                            clk=0;
                            RAM[AR.to_ulong()]=AC;
                        }
                    }
                    else if(commandLine.at(0)=="BUN")
                    {
                        int Ichecker;
                        if(clk==3)
                        {
                            clk++;
                            if(commandLine.length()>=1&&!isHex(commandLine.at(1))){
                                AR = allDatas[commandLine.at(1)+','];
                            }

                            if(commandLine.size()>=3 && commandLine.at(2)=='I')
                            {
                                ui->CurrentOper->setText("AR <- M[AR] ");
                                int tmpAR=AR.to_ulong();
                                for (int bitC=0;bitC<12;bitC++)
                                {
                                    AR[bitC]=RAM[tmpAR][bitC];
                                }
                                Ichecker=1;
                            }
                            else
                            {
                                Ichecker=0;

                            }
                        }
                        else if(clk==4)
                        {
                            ui->CurrentOper->setText("PC <- AR , SC <- 0");
                            SC=0;
                            clk=0;
                            PC=AR;
                            ///////////////////////////
                               lineStep=memoryToLine[AR.to_ulong()]-1;
                            ///////////////////////////
                            lineStep++;
                            memorystep=PC.to_ulong();
                        }
                    }
                    else if(commandLine.at(0)=="BSA")
                    {
                        if(clk==3)
                        {
                            clk++;
                            if(commandLine.size()>=3 && commandLine.at(2)=='I')
                            {
                                ui->CurrentOper->setText("AR <- M[AR] ");
                                bitset<12> tmpAR=AR;
                                for (int bitC=0;bitC<12;bitC++)
                                {
                                    AR[bitC]=RAM[tmpAR.to_ulong()][bitC];
                                }
                            }
                            else
                            {}
                        }
                        else if(clk==4)
                        {
                            ui->CurrentOper->setText("M[AR] <- PC , AR <- AR+1");
                            clk++;
                            incrAR();
                            for (int bitC=0;bitC<12;bitC++)
                            {
                                RAM[(AR.to_ulong())-1][bitC]=PC[bitC];
                            }
                        }
                        else if(clk==5)
                        {
                            clk=0;
                            PC=AR;
                            lineStep=allDatas[commandLine.at(1)+","];
                            lineStep++;
                            SC=0;
                            memorystep=PC.to_ulong();
                            ui->CurrentOper->setText("PC <- AR , SC <- 0");
                        }
                    }
                    else if(commandLine.at(0)=="ISZ")
                    {
                        if(clk==3)
                        {
                            clk++;
                            if(commandLine.size()>=3 && commandLine.at(2)=='I')
                            {
                                ui->CurrentOper->setText("AR <- M[AR] ");
                                bitset<12> tmpAR=AR;
                                for (int bitC=0;bitC<12;bitC++)
                                {
                                    AR[bitC]=RAM[tmpAR.to_ulong()][bitC];
                                }
                            }
                            else
                            {}
                        }
                        else if(clk==4)
                        {
                            ui->CurrentOper->setText("DR <- M[AR]");
                            clk++;
                            DR=RAM[AR.to_ulong()];
                        }
                        else if(clk==5)
                        {
                            ui->CurrentOper->setText("DR <- DR+1");
                            clk++;
                            incrDR();
                        }
                        else if(clk==6)
                        {
                            SC=0;
                            clk=0;
                            lineStep++;
                            RAM[AR.to_ulong()]=DR;
                            ui->CurrentOper->setText("M[AR] <- DR , SC <- 0");
                            if(DR.to_ulong()==0)
                            {
                                incrPC();
                                lineStep++;
                                memorystep++;
                                ui->CurrentOper->setText("PC <- PC+1 , M[AR] <- DR , SC <- 0");
                            }
                        }
                    }
                    else if(commandLine.at(0)=="INP")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        bool ok=1;
                        INPR=ui->Input->text().toInt(&ok,16);
                        for (int bitC=0;bitC<8;bitC++)
                        {
                            AC[bitC]=INPR[bitC];
                        }
                        FGI=0;
                        ui->CurrentOper->setText("AC(0-7) <- INPR , FGI <- 0 , SC <- 0");
                    }
                    else if(commandLine.at(0)=="OUT")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        for (int bitC=0;bitC<8;bitC++)
                        {
                            OUTR[bitC]=AC[bitC];
                        }
                        FGO=0;

                        ui->Output->setText(bitset8toQString(OUTR));
                        ui->CurrentOper->setText("OUTR <- AC(0-7) , FGO <- 0 , SC <- 0");
                                            }
                    else if(commandLine.at(0)=="SKI")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        ui->CurrentOper->setText("SC <- 0");
                        if(FGI==1)
                        {
                            incrPC();
                            lineStep++;
                            memorystep++;
                            ui->CurrentOper->setText("PC <- PC+1 , SC <- 0");
                        }
                    }
                    else if(commandLine.at(0)=="SKO")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        ui->CurrentOper->setText("SC <- 0");
                        if(FGO==1)
                        {
                            incrPC();
                            lineStep++;
                            memorystep++;
                            ui->CurrentOper->setText("PC <- PC+1 , SC <- 0");
                        }
                    }
                    else if(commandLine.at(0)=="ION")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        IEN=1;
                        ui->CurrentOper->setText("IEN <- 1 , SC <- 0");
                    }
                    else if(commandLine.at(0)=="IOF")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        IEN=0;
                        ui->CurrentOper->setText("IEN <- 0 , SC <- 0");
                    }
                    else if(commandLine.at(0)=="CLA")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        AC=0;
                        ui->CurrentOper->setText("AC <- 0  , SC <- 0 ");
                    }
                    else if(commandLine.at(0)=="CLE")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        E=0;
                        ui->CurrentOper->setText("E <- 0  , SC <- 0 ");
                    }
                    else if(commandLine.at(0)=="CMA")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        AC.flip();
                        ui->CurrentOper->setText("AC <- ~AC  , SC <- 0 ");
                    }
                    else if(commandLine.at(0)=="CME")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        E.flip();
                        ui->CurrentOper->setText("E <- ~E  , SC <- 0 ");
                    }
                    else if(commandLine.at(0)=="CIR")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        E[0] = AC[0];
                        AC = AC >> 1;
                        AC[15] = E[0];
                       ui->CurrentOper->setText("AC <- shr  , AC(15)<-E , E <- AC(0) ");
                    }
                    else if(commandLine.at(0)=="CIL")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        E[0] = AC[15];
                        AC = AC << 1;
                        AC[0] = E[0];
                        ui->CurrentOper->setText("AC <- shl  , AC(0)<-E , E <- AC(15) ");
                    }
                    else if(commandLine.at(0)=="INC")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        incrAC();
                        ui->CurrentOper->setText("AC <- AC+1  , SC <- 0 ");
                    }
                    else if(commandLine.at(0)=="SPA")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        ui->CurrentOper->setText("SC <- 0 ");
                        if(AC[15]==0)
                        {
                            ui->CurrentOper->setText("PC <- PC+1  , SC <- 0 ");
                            incrPC();
                            lineStep++;
                            memorystep++;
                        }
                    }
                    else if(commandLine.at(0)=="SNA")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        ui->CurrentOper->setText("SC <- 0 ");
                        if(AC[15]==1)
                        {
                            incrPC();
                            lineStep++;
                            memorystep++;
                            ui->CurrentOper->setText("PC <- PC+1  , SC <- 0 ");
                        }
                    }
                    else if(commandLine.at(0)=="SZA")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        ui->CurrentOper->setText("SC <- 0 ");
                        if(AC.to_ulong()==0)
                        {
                            incrPC();
                            lineStep++;
                            memorystep++;
                            ui->CurrentOper->setText("PC <- PC+1  , SC <- 0 ");
                        }
                    }
                    else if(commandLine.at(0)=="SZE")
                    {
                        SC=0;
                        clk=0;
                        lineStep++;
                        ui->CurrentOper->setText("SC <- 0 ");
                        if(E.to_ulong()==0)
                        {
                            incrPC();
                            lineStep++;
                            memorystep++;
                            ui->CurrentOper->setText("PC <- PC+1 , SC <- 0 ");
                        }
                    }
                    else if(commandLine.at(0)=="HLT")
                    {
                        S=0;
                        SC=0;
                        clk=0;
                        lineStep++;
                        ui->RUN->setEnabled(false);
                        ui->NEXT->setEnabled(false);
                        ui->CurrentOper->setText("S <- 0");
                        ui->Output->setText("Run successfuly \n");
                        if(printing)
                        {
                            printReg();
                            printTable();
                        }
                        return;
                    }
                    else if(commandLine.at(0)=="END")
                    {
                        clk=0;
                        lineStep++;
                        if(printing)
                        {
                            printReg();
                            printTable();
                        }
                        ui->Output->setText("Run successfully\n");
                        ui->RUN->setEnabled(false);
                        ui->NEXT->setEnabled(false);
                        return;
                    }
                    else
                    {
                        clk=0;
                        lineStep++;
                        if(printing)
                        {
                            printReg();
                            printTable();
                        }
                        ui->Output->setText("ERROR!!! COMMAND NOT FOUND \n");
                        ui->RUN->setEnabled(false);
                        ui->NEXT->setEnabled(false);
                        return;
                    }
                    if(printing)
                    {
                        printReg();
                        printTable();
                    }
        }
}


void MainWindow::on_COMPILE_clicked()
{
    is_error_showed = 0;
    on_RESET_clicked();
    is_compiled=1;
    int lc=0;
    int lc1=0;
    ui->Output->clear();
    commands = ui->Editor->toPlainText().split('\n', Qt::SkipEmptyParts);
    commandsCount=commands.size();
    int endp1=0;
    for(int i=0;i<commandsCount;i++)
    {
        if(lc>4096)
        {
            ui->Output->setText("ERROR!!! Your RAM have no more than 4096 units\n");
            is_error_showed = 1;
            is_compiled=0;
            break;
        }
        QStringList commandLine = commands.at(i).split(' ', Qt::SkipEmptyParts);
        if(i==0){
            if(commandLine.at(0)=="ORG")
                    {
                        if(isHex(commandLine.at(1)))
                        {
                            bool ok=1;
                            lc1=commandLine.at(1).toInt(&ok,16);
                            continue;

                        }
                        else
                        {
                            ui->Output->setText("ERROR!!! after ORG, HEX is need \n");
                            is_error_showed = 1;
                            is_compiled=0;
                            break;
                        }
                    }
            else{
                ui->Output->setText("ERROR!!! You do not specifiy ORG \n");
                is_error_showed = 1;
                is_compiled=0;
                break;
            }
        }
        if(commandLine.at(0)[commandLine.at(0).size()-1]==',')
        {
            QString wait="";
            for(int cw=0;cw<commandLine.at(0).size()-1;cw++)
            {
                wait+=commandLine.at(0)[cw];
            }
            firstallDatas[wait]=lc1;
        }
        memoryToLine[lc1]=i;
        lc1++;
    }

    for(int i=0;i<commandsCount;i++)
    {
        if(lc>4096)
        {
            ui->Output->setText("ERROR!!! Your RAM have no more than 4096 units\n");
            is_error_showed = 1;
            is_compiled=0;
            break;
        }

        QStringList commandLine = commands.at(i).split(' ', Qt::SkipEmptyParts);
            if(commandLine.at(0)=="ORG")
            {
                    bool ok=1;
                    lc=commandLine.at(1).toInt(&ok,16);
                    continue;
            }
            else if(commandLine.at(0)[commandLine.at(0).size()-1]==',')
            {
                allDatas[commandLine.at(0)]=i;
                QTableWidgetItem *itmlabel = new QTableWidgetItem();
                itmlabel->setText(commandLine.at(0));
                ui->RAM->setItem(lc,0,itmlabel);
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                int convertNumber;
                if(commandLine.at(1)=="HEX")
                {
                    if(isHex(commandLine.at(2)))
                    {
                        bool ok=1;
                        convertNumber=commandLine.at(2).toInt(&ok,16);
                        RAM[lc]=convertNumber;
                        lc++;
                        continue;
                    }
                    else
                    {
                        ui->Output->setText("ERROR!!! line:"+QString::number(i+1)+"\nInvalid chars after HEX flag \n");
                        is_compiled=0;
                        is_error_showed = 1;
                        break;
                    }
                }
                else if(commandLine.at(1)=="DEC")
                {
                    if(isHex(commandLine.at(2)))
                    {
                        bool ok=1;
                        convertNumber=commandLine.at(2).toInt(&ok,10);
                        RAM[lc]=convertNumber;
                        lc++;
                        continue;
                    }
                    else
                    {
                        ui->Output->setText("ERROR!!! line: "+QString::number(i+1)+" \nInvalid chars after HEX flag \n");
                        is_compiled=0;
                        is_error_showed = 1;
                        break;
                    }
                }
                else
                {
                    for(int x=0;x<(commandLine.length())-1;x++)
                    {
                        commandLine[x]=commandLine[x+1];
                    }

                }

            }
            if(commandLine.at(0)=="DEC")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(commandLine.length()>1 && isHex(commandLine.at(1)) )
                {
                    bool ok=1;
                    int convertNumber=commandLine.at(1).toInt(&ok,10);
                    RAM[lc]=convertNumber;
                }
                else
                {
                    ui->Output->setText("ERROR!!! line: "+QString::number(i+1)+" \nInvalid chars after HEX flag \n");
                    is_error_showed = 1;
                    is_compiled=0;
                    break;
                }

            }
            else if(commandLine.at(0)=="HEX")
            {

                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(commandLine.length()>1 && isHex(commandLine.at(1)))
                {
                    bool ok=1;
                    int convertNumber=commandLine.at(1).toInt(&ok,16);
                    RAM[lc]=convertNumber;
                }
                else
                {
                    ui->Output->setText("ERROR!!! line: "+QString::number(i+1)+" \nInvalid chars after HEX flag \n");
                    is_error_showed = 1;
                    is_compiled=0;
                    break;
                }
            }

            else if(commandLine.at(0)=="AND")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(firstallDatas[commandLine.at(1)]==0)
                {
                    ui->Output->setText("Error!!! line: "+QString::number(i+1)+" The "+commandLine.at(1)+" lable does not exist");
                    is_compiled=0;
                    is_error_showed = 1;
                    break;
                }
                if(commandLine.size()>=3 && commandLine.at(2)=='I')
                {
                    RAM[lc]=0x8000+firstallDatas[commandLine.at(1)];
                }
                else
                {
                    RAM[lc]=0x0000+firstallDatas[commandLine.at(1)];
                }

            }
            else if(commandLine.at(0)=="ADD")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(firstallDatas[commandLine.at(1)]==0)
                {
                    ui->Output->setText("Error!!! line: "+QString::number(i+1)+" The "+commandLine.at(1)+" lable does not exist");
                    is_compiled=0;
                    is_error_showed = 1;
                    break;

                }
                if(commandLine.size()>=3 && commandLine.at(2)=='I')
                {
                    RAM[lc]=0x9000+firstallDatas[commandLine.at(1)];
                }
                else
                {
                    RAM[lc]=0x1000+firstallDatas[commandLine.at(1)];
                }

            }

            else if(commandLine.at(0)=="LDA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(firstallDatas[commandLine.at(1)]==0)
                {
                    ui->Output->setText("Error!!! line: "+QString::number(i+1)+" The "+commandLine.at(1)+" lable does not exist");
                    is_compiled=0;
                    is_error_showed = 1;
                    break;
                }
                if(commandLine.size()>=3 && commandLine.at(2)=='I')
                {
                    RAM[lc]=0xA000+firstallDatas[commandLine.at(1)];
                }
                else
                {
                    RAM[lc]=0x2000+firstallDatas[commandLine.at(1)];
                }
            }

            else if(commandLine.at(0)=="STA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(firstallDatas[commandLine.at(1)]==0)
                {
                    ui->Output->setText("Error!!! line: "+QString::number(i+1)+" The "+commandLine.at(1)+" lable does not exist");
                    is_compiled=0;
                    is_error_showed = 1;
                    break;

                }
                if(commandLine.size()>=3 && commandLine.at(2)=='I')
                {
                    RAM[lc]=0xB000+firstallDatas[commandLine.at(1)];
                }
                else
                {
                    RAM[lc]=0x3000+firstallDatas[commandLine.at(1)];
                }

            }

            else if(commandLine.at(0)=="BUN")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(firstallDatas.find(commandLine.at(1))==firstallDatas.end())
                {
                    ui->Output->setText("Error!!! line: "+QString::number(i+1)+" The "+commandLine.at(1)+" lable does not exist");
                    is_compiled=0;
                    is_error_showed = 1;
                    break;
                }
                if(commandLine.size()>=3 && commandLine.at(2)=='I')
                {
                    RAM[lc]=0xC000+firstallDatas[commandLine.at(1)];
                }
                else
                {
                    RAM[lc]=0x4000+firstallDatas[commandLine.at(1)];
                }
            }
            else if(commandLine.at(0)=="BSA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(firstallDatas.find(commandLine.at(1))==firstallDatas.end())
                {
                    ui->Output->setText("Error!!! line: "+QString::number(i+1)+" The "+commandLine.at(1)+" lable does not exist");
                    is_compiled=0;
                    is_error_showed = 1;
                    break;
                }
                if(commandLine.size()>=3 && commandLine.at(2)=='I')
                {
                    RAM[lc]=0xD000+firstallDatas[commandLine.at(1)];
                }
                else
                {
                    RAM[lc]=0x5000+firstallDatas[commandLine.at(1)];
                }
            }

            else if(commandLine.at(0)=="ISZ")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                if(firstallDatas.find(commandLine.at(1))==firstallDatas.end())
                {
                    ui->Output->setText("Error!!! line: "+QString::number(i+1)+" The "+commandLine.at(1)+" lable does not exist");
                    is_compiled=0;
                    is_error_showed = 1;
                    break;
                }
                if(commandLine.size()>=3 && commandLine.at(2)=='I')
                {
                    RAM[lc]=0xE000+firstallDatas[commandLine.at(1)];
                }
                else
                {
                    RAM[lc]=0x6000+firstallDatas[commandLine.at(1)];
                }
            }

            else if(commandLine.at(0)=="INP")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0xf800;
            }

            else if(commandLine.at(0)=="OUT")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0xf400;
            }
            else if(commandLine.at(0)=="SKI")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0xf200;
            }
            else if(commandLine.at(0)=="SKO")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0xf100;
            }
            else if(commandLine.at(0)=="ION")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0xf080;
            }
            else if(commandLine.at(0)=="IOF")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0xf040;
            }
            else if(commandLine.at(0)=="CLA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7800;
            }

            else if(commandLine.at(0)=="CLE")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7400;
            }
            else if(commandLine.at(0)=="CMA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7200;
            }
            else if(commandLine.at(0)=="CME")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7100;
            }
            else if(commandLine.at(0)=="CIR")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7080;
            }
            else if(commandLine.at(0)=="CIL")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7040;
            }
            else if(commandLine.at(0)=="INC")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7020;
            }
            else if(commandLine.at(0)=="SPA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7010;
            }
            else if(commandLine.at(0)=="SNA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7008;
            }
            else if(commandLine.at(0)=="SZA")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7004;
            }
            else if(commandLine.at(0)=="SZE")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7002;
            }
            else if(commandLine.at(0)=="HLT")
            {
                QTableWidgetItem *itmintraction = new QTableWidgetItem();
                itmintraction->setText(commands.at(i));
                ui->RAM->setItem(lc,2,itmintraction);
                RAM[lc]=0x7001;
            }
            else if(commandLine.at(0)=="END")
            {
                endp1=1;
                printTable();
                if(is_compiled)
                {
                    ui->Output->setText("Compiled successfully\n");
                }
                else
                {
                    ui->Output->append("\n ERROR!!!\n");
                    is_error_showed = 1;
                }
                break;
            }
            else
            {
                ui->Output->setText("ERROR!!! line: "+QString::number(i+1)+"  Command not found\n");
                ui->Output->append(commands.at(i));
                is_error_showed = 1;
                is_compiled=0;
                break;
            }
            lc++;
    }
    if(!endp1 && is_error_showed == 0)
    {
        ui->Output->setText("ERROR!!! You did not specify END\n");
        is_compiled=0;
    }
}



void MainWindow::printReg()
{
    ui->SC->setText(QString::number( SC.to_ulong(), 16 ).toUpper());
    ui->PC->setText(QString::number( PC.to_ulong(), 16 ).toUpper());
    ui->AR->setText(QString::number( AR.to_ulong(), 16 ).toUpper());
    ui->IR->setText(QString::number( IR.to_ulong(), 16 ).toUpper());
    ui->DR->setText(QString::number( DR.to_ulong(), 16 ).toUpper());
    ui->AC->setText(QString::number( AC.to_ulong(), 16 ).toUpper());
    ui->TR->setText(QString::number( TR.to_ulong(), 16 ).toUpper());
    ui->INPR->setText(QString::number( INPR.to_ulong(), 16 ).toUpper());
    ui->OUTR->setText(QString::number( OUTR.to_ulong(), 16 ).toUpper());
    ui->I->setText(QString::number( I.to_ulong(), 16 ).toUpper());
    ui->S->setText(QString::number( S.to_ulong(), 16 ).toUpper());
    ui->E->setText(QString::number( E.to_ulong(), 16 ).toUpper());
    ui->R->setText(QString::number( R.to_ulong(), 16 ).toUpper());
    ui->IEN->setText(QString::number( IEN.to_ulong(), 16 ).toUpper());
    ui->FGI->setText(QString::number( FGI.to_ulong(), 16 ).toUpper());
    ui->FGO->setText(QString::number( FGO.to_ulong(), 16 ).toUpper());
}

void MainWindow::printTable()
{
    if(reseter)
    {
        ui->RAM->setRowCount(0);
        for(int v=0;v<4096;v++)
        {
            QString address = QString::number( v, 16 ).toUpper();
            QTableWidgetItem *itmaddr = new QTableWidgetItem();
            QTableWidgetItem *itmHex = new QTableWidgetItem();
            itmaddr->setText(address);
            itmHex->setText("0000");
            ui->RAM->insertRow(v);
            ui->RAM->setItem(v,1,itmaddr);
            ui->RAM->setItem(v,3,itmHex);
            reseter=0;
        }
    }
    else
    {
        for(int v=0;v<4096;v++)
        {
            QString address = QString::number( v, 16 ).toUpper();
            QTableWidgetItem *itmaddr = new QTableWidgetItem();
            QTableWidgetItem *itmHex = new QTableWidgetItem();
            itmaddr->setText(address);
            QString checkerString =QString::number( RAM[v].to_ulong(), 16 ).toUpper();
            if(checkerString.size()==3){
                checkerString = "0" + checkerString;
            }
            else if(checkerString.size()==2){
                checkerString = "00" + checkerString;
            }
            else if(checkerString.size()==1){
                checkerString = "000" + checkerString;
            }
            itmHex->setText(checkerString);
            ui->RAM->setItem(v,1,itmaddr);
            ui->RAM->setItem(v,3,itmHex);
        }
    }
}

void MainWindow::on_Save_triggered()
{
    if(is_saved=="")
    {
        on_Save_as_triggered();
    }
    else
    {
        ofstream f;
        f.open(is_saved.toLocal8Bit(),ios::out);
        f<<ui->Editor->toPlainText().toStdString();
        f.flush();
        f.close();
    }
}


void MainWindow::on_Save_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save as"), "",tr("(*.txt)"));
    if (fileName.isEmpty())
         return;
     else {
        ofstream f;
        f.open(fileName.toLocal8Bit(),ios::out);
        f<<ui->Editor->toPlainText().toStdString();
        f.flush();
        f.close();
        is_saved=fileName;
    }
}


void MainWindow::on_Exit_triggered()
{
    this->close();
}


void MainWindow::on_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open"), "",tr("(*.txt)"));
    if (fileName.isEmpty())
        return;
    else {
        ui->Editor->clear();
        is_saved=fileName;
        ifstream infile;
        infile.open(fileName.toLocal8Bit());
        char tmp[300];
        while(infile.eof()!=true)
        {
            infile.getline(tmp,300);
            ui->Editor->insertPlainText(QString::fromStdString(tmp));
            ui->Editor->insertPlainText("\n");
            is_compiled=0;
        }
    }
}


void MainWindow::on_New_triggered()
{
    ui->Editor->clear();
    is_saved="";
    is_compiled=0;
}


void MainWindow::on_RESET_clicked()
{

    reseter=1;
    for(int i=0;i<4096;i++)
    {
        RAM[i].reset();
    }
    SC.reset();
    PC.reset();
    AR.reset();
    IR.reset();
    DR.reset();
    AC.reset();
    TR.reset();
    INPR.reset();
    OUTR.reset();
    I.reset();
    S.reset();
    E.reset();
    R.reset();
    IEN.reset();
    FGI.reset();
    FGO.reset();
    printTable();
    printReg();
    ui->Output->setText("");
    allDatas.clear();
    firstallDatas.clear();
    commands.clear();
    is_compiled=0;
    clk=0;
    lineStep=0;
    memorystep=0;
    run=0;
    printing=1;
    ui->RUN->setEnabled(true);
    ui->NEXT->setEnabled(true);
    ui->Input->setText("");
    ui->CurrentOper->setText("");
    memoryToLine.clear();
}



void MainWindow::on_RUN_clicked()
{
    if(!is_compiled)
    {
        ui->Output->setText("Before run, first you need to compile your code\n");
    }
    else
    {
        S=1;
        printing=0;
        run=1;
        while (S.to_ulong())
        {
            on_NEXT_clicked();
        }

        printReg();
        printTable();
    }
}

