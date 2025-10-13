/* Minimal subset of OpenSSL's e_os2.h required by the bundled SHA1 code.
 *
 * The original header provides extensive platform-detection macros.  For the
 * purposes of the standalone dedup benchmark we only need a handful of common
 * definitions so that the extracted SHA implementation compiles cleanly
 * without depending on a system OpenSSL installation.
 */
#ifndef HEADER_E_OS2_H
#define HEADER_E_OS2_H

#if defined(__sun) || defined(sun)
# define OPENSSL_SYS_SUN
#endif

#if defined(_WIN32) || defined(_WIN64)
# define OPENSSL_SYS_WIN32
#endif

#if defined(__VMS)
# define OPENSSL_SYS_VMS
#endif

#if defined(__CYGWIN__)
# define OPENSSL_SYS_CYGWIN
#endif

#if defined(__unix__) || defined(__unix) || defined(unix)
# define OPENSSL_SYS_UNIX
#endif

#if defined(__linux__) || defined(__linux)
# define OPENSSL_SYS_LINUX
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
# define OPENSSL_SYS_BSD
#endif

#if defined(__APPLE__) && defined(__MACH__)
# define OPENSSL_SYS_MACOSX
#endif

/* Fallbacks for data model detection used by sha.h. */
#if defined(__LP64__) || defined(_LP64)
# define __ILP64__
#endif

#endif /* HEADER_E_OS2_H */
