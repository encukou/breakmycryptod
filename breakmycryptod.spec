Name: breakmycryptod
Version: 0.1.0
Release: 1%{?dist}
Summary: Inflates the kernel entropy estimate whenever it drops too low

License: GPLv2+
URL: https://github.com/encukou/%{name}
Source0: %{name}-%{version}.tar.gz

BuildRequires: asciidoc

%description
Use this and your system, and all keys generated on it, will become insecure.

This daemon waits for the kernel's entropy estimate to fall low enough, raises
it, and starts waiting again. As a result, reading from the random device never
blocks, but it also doesn't return truly random numbers.

%prep
%setup -q

%build
make

%install
make install DESTDIR=$RPM_BUILD_ROOT LIBDIR=$RPM_BUILD_ROOT/%{_libdir}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%doc README COPYING

%{_mandir}/man8/breakmycryptod.8.gz

%{_sbindir}/breakmycryptod
%{_libdir}/systemd/system/breakmycryptod.service

%changelog
* Tue Sep 06 2011 Petr Viktorin <encukou@gmail.com> 0.1.0-1
- Initial version of the package
