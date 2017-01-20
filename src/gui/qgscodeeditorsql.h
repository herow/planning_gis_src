/***************************************************************************
    qgscodeeditorsql.h - A SQL editor based on QScintilla
     --------------------------------------
    Date                 : 06-Oct-2013
    Copyright            : (C) 2013 by Salvatore Larosa
    Email                : lrssvtml (at) gmail (dot) com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSCODEEDITORSQL_H
#define QGSCODEEDITORSQL_H

#include "qgscodeeditor.h"


/** \ingroup gui
 * A SQL editor based on QScintilla2. Adds syntax highlighting and
 * code autocompletion.
 * \note added in 2.6
 */
class GUI_EXPORT QgsCodeEditorSQL : public QgsCodeEditor
{
    Q_OBJECT

  public:
    QgsCodeEditorSQL( QWidget *parent = 0 );
    ~QgsCodeEditorSQL();

  private:
    //QgsCodeEditor *mSciWidget;
    //QWidget *mWidget;
    void setSciLexerSQL();
};

#endif
