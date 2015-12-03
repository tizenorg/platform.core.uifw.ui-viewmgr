Name:       ui-viewmgr
Summary:    UI VIEW MANAGER library
Version:    0.1.0
Release:    1
Group:      System/Libraries
License:    APLv2
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  edje-bin
BuildRequires:  pkgconfig(elementary)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(utilX)
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
export CFLAGS+=" -fvisibility=hidden"
export LDFLAGS+=" -fvisibility=hidden"
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

