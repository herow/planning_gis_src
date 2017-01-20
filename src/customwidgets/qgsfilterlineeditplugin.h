/***************************************************************************
   qgsfilterlineeditplugin.h
    --------------------------------------
   Date                 : 20.08.2014
   Copyright            : (C) 2014 Denis Rouzaud
   Email                : denis.rouzaud@gmail.com
***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/

#ifndef QGSFILTERLINEEDITPLUGIN_H
#define QGSFILTERLINEEDITPLUGIN_H

#include <QDesignerExportWidget>
#include <QDesignerCustomWidgetInterface>


class CUSTOMWIDGETS_EXPORT QgsFilterLineEditPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES( QDesignerCustomWidgetInterface )

  public:
    explicit QgsFilterLineEditPlugin( QObject *parent = 0 );

  private:
    bool mInitialized;

    // QDesignerCustomWidgetInterface interface
  public:
    QString name() const override;
    QString group() const override;
    QString includeFile() const override;
    QIcon icon() const override;
    bool isContainer() const override;
    QWidget *createWidget( QWidget *parent ) override;
    bool isInitialized() const override;
    void initialize( QDesignerFormEditorInterface *core ) override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QString domXml() const override;
};
#endif // QGSFILTERLINEEDITPLUGIN_H
