#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "launchtask/launch_task_n_parser.h"
#include <QFile>
#include <QTextStream>
#include <cstdlib>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mclaucnh)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    if (it_has_username == true){
        //simple arguments
        //I know there's a easier way but i dont know
        ui->output->clear();
        jvmargs.clear();
        gameargs.clear();
        jvmargs.append("java");
        jvmargs.append("-Xmx2G");
        jvmargs.append("-Xms2G");
        jvmargs.append("-XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump");
        jvmargs.append("-Xss1M");
        jvmargs.append("-Djava.library.path=" + natdir);
        jvmargs.append("-Djna.tmpdir=" + natdir);
        jvmargs.append("-Dorg.lwjgl.system.SharedLibraryExtractPath=" + natdir);
        jvmargs.append("-Dio.netty.native.workdir=" + natdir);
        jvmargs.append("-Dminecraft.launcher.brand=java-custom");
        jvmargs.append("-Dminecraft.launcher.version=1.0");
        jvmargs.append("-cp ");

        gameargs.append("; net.minecraft.client.main.Main");
        gameargs.append("--username");
        gameargs.append(username);
        gameargs.append("--version");
        gameargs.append(defver);
        gameargs.append("--gameDir");
        gameargs.append(mcpath);
        gameargs.append(" --assetsDir");
        gameargs.append(assetdir);
        gameargs.append("--assetIndex");
        gameargs.append("24");
        gameargs.append("--uuid");
        gameargs.append("uuid");
        gameargs.append("--accessToken");
        gameargs.append("0");
        gameargs.append("--userType");
        gameargs.append("legacy");
        gameargs.append("--versionType");
        gameargs.append("release");
        gameargs.append("--width");
        gameargs.append("854");
        gameargs.append("--height");
        gameargs.append("480");
        QFile batfile("mcprocess.bat");
        if (!batfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            ui->output->append("<font color='red'>" + err_when_reading_file);
        }
        QTextStream out(&batfile);
        out << jvmargs.join(" ");
        out << classpath.join(";");
        out << gameargs.join(" ");
        batfile.close();
        //i prefered this way
        mcprocess.setProgram("mcprocess.bat");
        mcprocess.start();
        mcprocess.waitForFinished();
        //yes i know that's a awfull way to read the output
        ui->output->append("<font color='purple'>" + mcprocess.readAllStandardOutput());
        if (!mcprocess.waitForStarted()) {
            ui->output->append("<font color='red'>" + process_err_str + mcprocess.errorString());
        }
    }else{
        ui->output->append("<font color='red'>" + no_username_text);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //username dedector
    username = ui->usrnm->text();
    it_has_username = true;
    if (username == ""){
        ui->output->append("<font color='red'>" + username_is_empty);
        it_has_username = false;
    }else{
        ui->output->append("<font color='green'>" + username_created + username);
    }
}



void MainWindow::on_commandLinkButton_clicked()
{
    system("start https://github.com/Awthu1233");
    //if the button open the terminal, dont worry its normal :)
}


