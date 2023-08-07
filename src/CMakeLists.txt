set(SOURCE_FILES main.cpp
				 QBrowserApp.cpp
				 QConnectionDialog.cpp
				 QSqlQueryPanel.cpp
				 QConnectionCtrl.cpp
				 QDbTableView.cpp
				 QQueryHighlighter.cpp)
				 
set(HEADERS QBrowserApp.h
			QConnectionDialog.h
			QSqlQueryPanel.h
			QConnectionCtrl.h
			QDbTableView.h
			QQueryHighlighter.h)
	
if(WIN32)
	set(RESOURCES res/app_icon.rc)
	source_group("Resource files" FILES ${RESOURCES}) 
else()
	qt_add_resources(RESOURCES res/app_icon.qrc)
endif()

qt_add_executable(qSQLbrowser MANUAL_FINALIZATION ${SOURCE_FILES} ${HEADERS} ${RESOURCES})