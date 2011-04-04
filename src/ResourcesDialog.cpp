/*
	This is part of TeXworks, an environment for working with TeX documents
	Copyright (C) 2007-2011  Jonathan Kew, Stefan Löffler

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	For links to further information, or to contact the author,
	see <http://texworks.org/>.
*/

#include "ResourcesDialog.h"
#include "ConfigurableApp.h"
#include "TWUtils.h"

ResourcesDialog::ResourcesDialog(QWidget *parent)
: QDialog(parent)
{
	init();
}

void ResourcesDialog::init()
{
	QSETTINGS_OBJECT(s);

	setupUi(this);
	
#ifdef Q_WS_WIN
	if(ConfigurableApp::instance()->getSettingsFormat() == QSettings::NativeFormat)
		locationOfSettings->setText(tr("Registry (%1)").arg(s.fileName()));
	else
		locationOfSettings->setText(QString("<a href=\"file://%1\">%1</a>").arg(s.fileName()));
#else
	locationOfSettings->setText(QString("<a href=\"file://%1\">%1</a>").arg(s.fileName()));
#endif

	locationOfResources->setText(QString("<a href=\"file://%1\">%1</a>").arg(TWUtils::getLibraryPath(QString(), false)));

	connect(locationOfSettings, SIGNAL(linkActivated(const QString&)), this, SLOT(openLocation(const QString&)));
	connect(locationOfResources, SIGNAL(linkActivated(const QString&)), this, SLOT(openLocation(const QString&)));

	adjustSize();

// TODO: Implement Details (e.g., files that are versioned, ...)
//	connect(labelDetails, SIGNAL(linkActivated(const QString&)), this, SLOT(toggleDetails()));
//	toggleDetails();
}

/*
void ResourcesDialog::toggleDetails()
{
	if(groupResources->isVisibleTo(this)) {
		groupResources->hide();
		labelDetails->setText(QString("<a href=\"#\">%1</a>").arg(tr("Show Details")));
	}
	else {
		groupResources->show();
		labelDetails->setText(QString("<a href=\"#\">%1</a>").arg(tr("Hide Details")));
	}
	adjustSize();
}
*/

// static
QDialog::DialogCode ResourcesDialog::doResourcesDialog(QWidget *parent)
{
	ResourcesDialog dlg(parent);

	dlg.show();

	QDialog::DialogCode result = (DialogCode)dlg.exec();
	return result;
}
