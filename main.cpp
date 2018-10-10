//------------------------------------------------
#include "rm_str.h"
#include <QApplication>
#include <QMessageBox>
//------------------------------------------------
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSystemSemaphore semaphore("<RM_STR_1>", 1);
	semaphore.acquire();

#ifndef Q_OS_WIN32
	QSharedMemory nix_fix_shared_memory("<RM_STR_2>");
	if(nix_fix_shared_memory.attach())
	{
			nix_fix_shared_memory.detach();
	}
#endif

	QSharedMemory sharedMemory("<RM_STR_2>");
	bool is_running;
	if (sharedMemory.attach())
	{
			is_running = true;
	}
	else
	{
			sharedMemory.create(1);
			is_running = false;
	}
	semaphore.release();

	if(is_running)
	{
			QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setText("Приложение уже запущено.\n"
											"Вы можете запустить только один экземпляр приложения.");
			msgBox.exec();
			return 1;
	}



	RM_STR w;
	w.showMaximized();

	return a.exec();
}
//------------------------------------------------
