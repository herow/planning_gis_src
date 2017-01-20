#ifndef YOUXUANDOCKWIDGET_H
#define YOUXUANDOCKWIDGET_H

#include <QDockWidget>
#include <QSqlDatabase>
class QDataWidgetMapper;
class QSqlTableModel;
class ChuBuFangAnForm;
class QSqlQueryModel;
class WenTi_CeLueForm;
class fangtang;
class FinalFanganForm;
class View;
class QTableView;
namespace Ui {
class YouXuanDockWidget;
}

class YouXuanDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit YouXuanDockWidget(QWidget *parent = 0);
    ~YouXuanDockWidget();

private:
    Ui::YouXuanDockWidget *ui;
    QSqlTableModel *modelPro_Strategy;
    QSqlTableModel *model_InitialStrategy;
    QSqlTableModel *model_FinalStrategy;

    QSqlQueryModel *model_SurveyForm;
    QSqlQueryModel *model_SemiSurvey;
    QSqlQueryModel *model_SpecStatus;
    QSqlTableModel *model_strategy;
    QSqlQueryModel *model_PublicOpinion;
    QSqlQueryModel *model_GovOpinion;
    QSqlTableModel *model_youxuan;

    fangtang *wid_SemiSurvey;
    fangtang *wid_SpecStatus;
    fangtang *wid_PublicOpinion;
    fangtang *wid_GovOpinion;
    WenTi_CeLueForm *wid_wenti_celue;
    ChuBuFangAnForm *chubufangan;
    FinalFanganForm *wid_finalStrategy;
    View * wid_picview;
	
private slots:
    void show_kongxin_status();
    void show_surveyForm();
    void show_picturecollect();
    void show_ProblemStrategy();
    void show_specstatus();
    void show_semisurvey();
    void show_InitStrategy();
    void show_PublicOpinion();
    void show_GovOpinion();
    void show_FinalSolution();
    void setSelection(int idx);
	void deConnect(QObject*);

private:
   // bool createConnetion();
    QDataWidgetMapper *mapper;
	QSqlDatabase m_db;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // YOUXUANDOCKWIDGET_H
