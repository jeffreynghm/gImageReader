/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * common.hh
 * Copyright (C) 2013 Sandro Mani <manisandro@gmail.com>
 *
 * gImageReader is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gImageReader is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_HH
#define COMMON_HH

#include "config.h"
#include <gtkmm.h>
#include <iostream>

#ifdef ENABLE_NLS
	#include <libintl.h>
	#include <glibmm/i18n.h>
#else
	#define _(x) x
#endif

#ifdef G_OS_UNIX
	#define PATHSEP ':'
#else
	#define PATHSEP ';'
#endif

namespace sigc{
SIGC_FUNCTORS_DEDUCE_RESULT_TYPE_WITH_DECLTYPE
}

#define CONNECT(src, signal, ...) (src)->signal_##signal().connect(__VA_ARGS__)
#define CONNECTS(src, signal, ...) {auto sender = (src); sender->signal_##signal().connect(sigc::bind(__VA_ARGS__, sender)); }

// For local execution
#undef  PACKAGE_DATA_DIR
#define PACKAGE_DATA_DIR "data/"

#define APPLICATION_ID "org.gnome.gimagereader"
#define UI_FILE PACKAGE_DATA_DIR"/gimagereader.ui"
#define CHECKURL "http://sourceforge.net/projects/gimagereader/files/LATEST/download?use_mirror=autoselect"
#define DOWNLOADURL "http://sourceforge.net/projects/gimagereader/files"
#define CHANGELOGURL "http://sourceforge.net/projects/gimagereader/files/changelog.txt/download?use_mirror=autoselect"
#define MANUALURL PACKAGE_DATA_DIR"/manual.html"

struct Builder {
public:
	static Glib::RefPtr<Gtk::Builder> builder;
	Builder(const Glib::ustring& name){
		builder->get_widget(name, m_widget);
	}
	template <class T>
	operator T*(){ return (T*)m_widget; }

	template <class T>
	T* as(){ return (T*)m_widget; }
private:
	Gtk::Widget* m_widget;
};

#endif