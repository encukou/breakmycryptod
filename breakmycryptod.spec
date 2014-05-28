Name: breakmycryptod
Version: 0.1.0
Release: 3%{?dist}
Summary: Inflates the kernel entropy estimate whenever it drops too low

License: GPLv2+
URL: https://github.com/encukou/%{name}
Source0: %{name}-%{version}.tar.gz

BuildRequires: asciidoc
Requires(post): systemd
Requires(preun): systemd
Requires(postun): systemd
BuildRequires: systemd

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
make SBINDIR=$RPM_BUILD_ROOT/%{_sbindir} MANDIR=$RPM_BUILD_ROOT/%{_mandir} UNITDIR=$RPM_BUILD_ROOT/%{_unitdir} install

%clean
rm -rf $RPM_BUILD_ROOT

%post
%systemd_post %{name}.service

%preun
%systemd_preun %{name}.service

%postun
%systemd_postun_with_restart %{name}.service 

%files
%doc README COPYING

%attr(644, root, root) %{_mandir}/man8/breakmycryptod.8.gz
%attr(755, root, root) %{_sbindir}/breakmycryptod
%attr(644, root, root) %{_unitdir}/breakmycryptod.service

%changelog
* Tue Sep 06 2011 Petr Viktorin <encukou@gmail.com> 0.1.0-1
- Initial version of the package
