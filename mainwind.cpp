#include "mainwind.h"
#include "ui_mainwind.h"
#include "welwind.h"
#include <QString>
#include <QMessageBox>
#include <QStyle>

mainwind::mainwind(QWidget *_parent, const QString& path) :
    QMainWindow(_parent),
    ui(new Ui::mainwind),
    filepath(path)
{
    parent = _parent;
    ui->setupUi(this);

    //don't display the brightness and sepia sliders until they are necessary
    ui->brightnessWidget->hide();
    ui->sepiaWidget->hide();

    baseImg = new Image;

    baseImg->load(filepath);

    //resize currImg to make it fit in mainwind
    *baseImg = baseImg->scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    history.push_back(*baseImg);
    currImg = new Image(*baseImg);
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic); //display currImg in the central widget
}

mainwind::~mainwind()
{
    //Clean up all dynamically allocated member fields
    delete ui;
    delete currImg;
    delete baseImg;
}

QString mainwind::getFilePath()
{
    return filepath;
}

void mainwind::on_actionQuit_triggered()
{
    QApplication::quit();
}

void mainwind::on_actionAbout_Photo_Editor_triggered()
{
    QString about_text;
    about_text = "Welcome to PhotoEditor.\n";
    about_text += "Developed By: Clayton Jerlow and Deborah Orret \n";  
    about_text += "\nInstructions:\n\n";
    about_text += "To Open a Picture:\n";
    about_text += "When the welcome window opens up, type the path of your selected file into the text line about the continue button. Once you are sure that is the correct file path to your picture, press continue to begin editing.\n";
    about_text += "\nTo Edit a Picture:\n";
    about_text += "Click your desired tools or filters from either the toolbars or the menu bar. The respective effect will be automatically applied when you click any button.\n";
    about_text += "\nThe Top ToolBar has six buttons, in order : New, Save, Filters, Orientation Tools, Information, and Quit. The New button returns you back to the welcome window to begin a new project, the Save button saves your picture to your desktop, the Filters button toggles the Filter Toolbar on, the Orientation Tools button toggles the Orientation Toolbar on, this Information button opens instructions, and the Quit button closes the app. If you would like to hide the Filters/Orientations toolbar simply click the small “x” at the top of each one.";
    about_text += "\n\nThe left side tool bar, the Orientation Toolbar, includes to an easy access tool buttons needed to change the orientation of the picture, as well as the undo button. These orientation tools include, in order: flip, rotate 180,  rotate left, rotate right, undo, revert. The right side tool bar, the Filters Toolbar, includes the filters, in order: black and white, grayscale, aqua, rouge, veridian, negative, sepia, and the brightness.\n";

    QMessageBox::about (this, "About Photo Editor", about_text);
}


void mainwind::on_actionFilters_3_triggered()
{
    ui->FilterWidget->show();

}

void mainwind::on_actionTools_triggered()
{
    ui->StickerWidget->show();
}

void mainwind::on_actionUndo_triggered()
{
    if(history.size() > 1){
        history.pop_back();
        delete currImg;
        currImg = new Image(history[history.size()-1]);
    }
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_actionRevert_triggered()
{
    history.clear();
    history.push_back(*baseImg);
    *currImg = *baseImg;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic); //display currImg in the central widget
}

void mainwind::on_actionRotateRight_triggered()
{
    Image temp(*currImg);
    temp.rotateRight();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_actionRotateLeft_triggered()
{
    Image temp(*currImg);
    temp.rotateLeft();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_actionFlip_2_triggered()
{
    Image temp(*currImg);
    temp.mirror();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_actionRotate_180_triggered()
{
    Image temp(*currImg);
    temp.rotate180();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}


/* -----------FILTERS----------- */
void mainwind::on_blackAndWhite_clicked()
{
    Image temp(*currImg);
    temp.blackAndWhite();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_grayscale_clicked()
{
    Image temp(*currImg);
    temp.grayscale();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_aqua_clicked()
{
    Image temp(*currImg);
    temp.aqua();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_rouge_clicked()
{
    Image temp(*currImg);
    temp.rouge();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_veridian_clicked()
{
    Image temp(*currImg);
    temp.veridian();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_negative_clicked()
{
    Image temp(*currImg);
    temp.negative();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_brightness_clicked()
{
    ui->brightnessWidget->show();
}

void mainwind::on_brightSlider_sliderMoved(int position)
{
    //use temp Image until user wants to commit changes
    Image temp(*currImg);
    temp.brightness(position);
    QPixmap pic;
    pic.convertFromImage(temp);
    ui->picture->setPixmap(pic);
}

void mainwind::on_brightSave_clicked()
{
    //commit changes
    Image temp(*currImg);
    temp.brightness(ui->brightSlider->value());
    history.push_back(temp);
    *currImg = temp;
    //return brightSlider to original state
    ui->brightSlider->setValue(0);
    ui->brightnessWidget->hide();
}

void mainwind::on_sepia_clicked()
{
    Image temp(*currImg);
    temp.sepia(25, 25); //ensures filter is applied right after the click
    QPixmap pic;
    pic.convertFromImage(temp);
    ui->picture->setPixmap(pic);
    ui->sepiaWidget->show();
}

void mainwind::on_depthSlider_sliderMoved(int position)
{
    Image temp(*currImg);
    //use slider value to apply sepia at certain depth
    temp.sepia(position, ui->intensitySlider->value());
    QPixmap pic;
    pic.convertFromImage(temp);
    ui->picture->setPixmap(pic); 
}

void mainwind::on_intensitySlider_sliderMoved(int position)
{
    Image temp(*currImg);
    //use slider value to apply sepia at certain intensity
    temp.sepia(ui->depthSlider->value(), position);
    QPixmap pic;
    pic.convertFromImage(temp);
    ui->picture->setPixmap(pic);    
}

void mainwind::on_sepiaSave_clicked()
{
    //commit changes
    Image temp(*currImg);
    temp.sepia(ui->depthSlider->value(), ui->intensitySlider->value());
    history.push_back(temp);
    *currImg = temp;

    //set sliders to original states
    ui->depthSlider->setValue(25);
    ui->intensitySlider->setValue(25);
    ui->sepiaWidget->hide();
}

void mainwind::on_actionNew_triggered()
{
    parent->show();
    this->hide();
}

void mainwind::on_actionSave_triggered()
{
    save = new savewind(this, currImg, filepath);
    save->show();
    save->setWindowTitle("Save!");
    this->hide();
}


/* -----------TOOLBAR---------- */

void mainwind::on_flip_clicked()
{
    Image temp(*currImg);
    temp.mirror();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_rotate180_clicked()
{
    Image temp(*currImg);
    temp.rotate180();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_undo_clicked()
{
    if(history.size() > 1){
        history.pop_back();
        delete currImg;
        currImg = new Image(history[history.size()-1]);
    }
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_rotate_left_clicked()
{
    Image temp(*currImg);
    temp.rotateLeft();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}

void mainwind::on_rotate_right_clicked()
{
    Image temp(*currImg);
    temp.rotateRight();
    history.push_back(temp);
    *currImg = temp;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic);
}


void mainwind::on_revert_clicked()
{
    history.clear();
    history.push_back(*baseImg);
    *currImg = *baseImg;
    QPixmap pic;
    pic.convertFromImage(*currImg);
    ui->picture->setPixmap(pic); //display currImg in the central widget
}
