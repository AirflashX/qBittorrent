/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2006  Christophe Dumez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact : chris@qbittorrent.org
 */

#ifndef TRANSFERLISTWIDGET_H
#define TRANSFERLISTWIDGET_H

#include <QShortcut>
#include <QTreeView>
#include <libtorrent/version.hpp>
#include "qtorrenthandle.h"
#include "transferlistsortmodel.h"

class QBtSession;
class TransferListDelegate;
class MainWindow;
class TorrentModel;

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QStandardItemModel;
QT_END_NAMESPACE

enum TorrentFilter {FILTER_ALL, FILTER_DOWNLOADING, FILTER_COMPLETED, FILTER_PAUSED, FILTER_ACTIVE, FILTER_INACTIVE};

class TransferListWidget: public QTreeView {
  Q_OBJECT

public:
  TransferListWidget(QWidget *parent, MainWindow *main_window, QBtSession* BTSession);
  ~TransferListWidget();
  TorrentModel* getSourceModel() const;

public slots:
  void setSelectionLabel(QString label);
  void setRefreshInterval(int t);
  void setSelectedTorrentsLocation();
  void startSelectedTorrents();
  void startVisibleTorrents();
  void pauseSelectedTorrents();
  void pauseVisibleTorrents();
  void deleteSelectedTorrents();
  void deleteVisibleTorrents();
  void increasePrioSelectedTorrents();
  void decreasePrioSelectedTorrents();
  void topPrioSelectedTorrents();
  void bottomPrioSelectedTorrents();
  void copySelectedMagnetURIs() const;
  void openSelectedTorrentsFolder() const;
  void recheckSelectedTorrents();
  void setDlLimitSelectedTorrents();
  void setUpLimitSelectedTorrents();
  void setMaxRatioSelectedTorrents();
  void previewSelectedTorrents();
  void hidePriorityColumn(bool hide);
  void displayDLHoSMenu(const QPoint&);
  void applyNameFilter(const QString& name);
  void applyStatusFilter(int f);
  void applyLabelFilter(QString label);
  void previewFile(QString filePath);
  void removeLabelFromRows(QString label);
  void renameSelectedTorrent();

protected:
  int getRowFromHash(QString hash) const;
  QString getHashFromRow(int row) const;
  QModelIndex mapToSource(const QModelIndex &index) const;
  QModelIndex mapFromSource(const QModelIndex &index) const;
  QStringList getCustomLabels() const;
  void saveSettings();
  bool loadSettings();
  QStringList getSelectedTorrentsHashes() const;

protected slots:
  void torrentDoubleClicked(const QModelIndex& index);
  void displayListMenu(const QPoint&);
  void currentChanged(const QModelIndex& current, const QModelIndex&);
  void toggleSelectedTorrentsSuperSeeding() const;
  void toggleSelectedTorrentsSequentialDownload() const;
  void toggleSelectedFirstLastPiecePrio() const;
  void askNewLabelForSelection();

signals:
  void currentTorrentChanged(const QTorrentHandle &h);

private:
  TransferListDelegate *listDelegate;
  TorrentModel *listModel;
  TransferListSortModel *nameFilterModel;
  QSortFilterProxyModel *statusFilterModel;
  QSortFilterProxyModel *labelFilterModel;
  QBtSession* BTSession;
  MainWindow *main_window;
  QShortcut *editHotkey;
  QShortcut *deleteHotkey;
};

#endif // TRANSFERLISTWIDGET_H
