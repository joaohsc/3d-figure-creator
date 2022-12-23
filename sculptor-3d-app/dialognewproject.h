#ifndef DIALOGNEWPROJECT_H
#define DIALOGNEWPROJECT_H

#include <QDialog>
#include <QString>
/**
 *  @brief a classe dialog new project é um qdialog
 *  @details a classe é responsavel por definir as dimensões x,y e z do grid
 */

namespace Ui {
class DialogNewProject;
}

class DialogNewProject : public QDialog
{
    Q_OBJECT

public:
    /**
     *  @brief construtor do qdialog que representa o dialog que define as dimensões do grid
     */
    explicit DialogNewProject(QWidget *parent = nullptr);
    ~DialogNewProject();

    /**
     *  @brief método que recupera o valor x do texto enviado no dialog
     */
    QString get_x_dialog();

    /**
     *  @brief método que recupera o valor y do texto enviado no dialog
     */
    QString get_y_dialog();

    /**
     *  @brief método que recupera o valor z do texto enviado no dialog
     */
    QString get_z_dialog();

private:
    Ui::DialogNewProject *ui;
};

#endif // DIALOGNEWPROJECT_H
