#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<bitset>
#include<map>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    quint16 getE() { return E.to_ulong(); }
    quint16 getDR() { return DR.to_ulong(); }
    quint16 getAC() { return AC.to_ulong(); }
    bool getACleadingBit() { return AC[15]; }
    quint16 getIR() { return IR.to_ulong(); }
    quint16 getTR() { return TR.to_ulong(); }
    quint16 getAR() { return AR.to_ulong(); }
    quint16 getPC() { return PC.to_ulong(); }
    quint16 getINPR() { return INPR.to_ulong(); }
    quint16 getOUTR() { return OUTR.to_ulong(); }
    void setE(const quint16& E) { this->E = std::bitset<1>(E); }
    void setDR(const quint16& DR) { this->DR = std::bitset<16>(DR); }
    void setAC(const quint16& AC) { this->AC = std::bitset<16>(AC); }
    void setIR(const quint16& IR) { this->IR = std::bitset<16>(IR); }
    void setTR(const quint16& TR) { this->TR = std::bitset<16>(TR); }
    void setAR(const quint16& AR) { this->AR = std::bitset<12>(AR); }
    void setPC(const quint16& PC) { this->PC = std::bitset<12>(PC); }
    void setINPR(const quint8& INPR) { this->INPR = std::bitset<8>(INPR); }
    void setOUTR(const quint8& OUTR) { this->OUTR = std::bitset<8>(OUTR); }
    void incrAR() { setAR(getAR() + 1); }
    void incrPC() { setPC(getPC() + 1); }
    void incrDR() { setDR(getDR() + 1); }
    void incrAC() { setAC(getAC() + 1); }
    void incrTR() { setTR(getTR() + 1); }
    void emptyTable();
    void clrAR() { AR.reset(); }
    void clrPC() { PC.reset(); }
    void clrDR() { DR.reset(); }
    void clrAC() { AC.reset(); }
    void clrTR() { TR.reset(); }
    void arithmeticUnitADD();
    void arithmeticUnitCIR();
    void arithmeticUnitCIL();
    void printReg();
    void printTable();
    bool isHex(const QString& str);

private slots:
    void on_RUN_clicked();
    void on_COMPILE_clicked();

    void on_Save_triggered();

    void on_Save_as_triggered();

    void on_Exit_triggered();

    void on_Open_triggered();

    void on_New_triggered();

    void on_RESET_clicked();

    void on_NEXT_clicked();

private:
    Ui::MainWindow *ui;
    QString is_saved="";
    bitset<16> RAM[4096];
    bitset<16> IR,TR,AC,SC,DR;
    bitset<12> AR,PC;
    bitset<8> INPR,OUTR;
    bitset<1> E,I,S,R,IEN,FGI,FGO;
    map<QString,int> allDatas;
    map<QString,int> firstallDatas;
    QStringList commands;
    int commandsCount;
    int clk;
    int lineStep;
    int memorystep;
    bool reseter=1;
    bool is_compiled=0;
    bool printing;
    bool run;
    bool is_error_showed = 0;
    map<int,int> memoryToLine;
};
#endif // MAINWINDOW_H
