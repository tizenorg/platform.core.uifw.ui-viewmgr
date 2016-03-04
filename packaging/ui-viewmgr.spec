Name:       ui-viewmgr
Summary:    UI VIEW MANAGER library
Version:    0.1.1
Release:    1
Group:      System/Libraries
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(capi-appfw-application)
BuildRequires:  pkgconfig(capi-system-system-settings)
BuildRequires:  pkgconfig(capi-appfw-app-manager)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  app-core-efl-devel
BuildRequires:  efl-extension-devel
BuildRequires:  cmake
BuildRequires:  edje-bin
BuildRequires:  gettext-tools
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
UI VIEW MANAGER library

%package devel
Summary:    UI VIEW MANAGER library (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}
Requires:   capi-base-common-devel

%description devel
UI VIEW MANAGER library providing View management functionality(devel)

%prep
%setup -q

%build
cmake . -DCMAKE_INSTALL_PREFIX=/usr
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/usr/share/license
cp %{_builddir}/%{buildsubdir}/LICENSE %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/libui-viewmgr.so.*
%manifest %{name}.manifest
/usr/share/license/%{name}
/usr/share/edje/ui-viewmgr/ui-viewmgr.edj
/opt/usr/apps/ui-viewmgr/bin/*

%files devel
%defattr(-,root,root,-)
%{_includedir}/ui-viewmgr/*.h
%{_libdir}/*.so
%{_libdir}/pkgconfig/ui-viewmgr.pc
