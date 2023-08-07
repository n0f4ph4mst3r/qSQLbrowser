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
	
qt_add_resources(RESOURCES res/icons.qrc)
if(WIN32)
	source_group("Resource files" FILES res/app_icon.rc res/icons.qrc)
	qt_add_executable(qSQLbrowser MANUAL_FINALIZATION ${SOURCE_FILES} ${HEADERS} ${RESOURCES} res/app_icon.rc)
else()
	qt_add_executable(qSQLbrowser MANUAL_FINALIZATION ${SOURCE_FILES} ${HEADERS} ${RESOURCES})
endif()