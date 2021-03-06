# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
if _swig_python_version_info >= (2, 7, 0):
    def swig_import_helper():
        import importlib
        pkg = __name__.rpartition('.')[0]
        mname = '.'.join((pkg, '_libzt')).lstrip('.')
        try:
            return importlib.import_module(mname)
        except ImportError:
            return importlib.import_module('_libzt')
    _libzt = swig_import_helper()
    del swig_import_helper
elif _swig_python_version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_libzt', [dirname(__file__)])
        except ImportError:
            import _libzt
            return _libzt
        try:
            _mod = imp.load_module('_libzt', fp, pathname, description)
        finally:
            if fp is not None:
                fp.close()
        return _mod
    _libzt = swig_import_helper()
    del swig_import_helper
else:
    import _libzt
del _swig_python_version_info

try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr(self, class_type, name):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    raise AttributeError("'%s' object has no attribute '%s'" % (class_type.__name__, name))


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except __builtin__.Exception:
    class _object:
        pass
    _newclass = 0


def zts_start(path, blocking):
    return _libzt.zts_start(path, blocking)
zts_start = _libzt.zts_start

def zts_startjoin(path, nwid):
    return _libzt.zts_startjoin(path, nwid)
zts_startjoin = _libzt.zts_startjoin

def zts_stop():
    return _libzt.zts_stop()
zts_stop = _libzt.zts_stop

def zts_core_running():
    return _libzt.zts_core_running()
zts_core_running = _libzt.zts_core_running

def zts_stack_running():
    return _libzt.zts_stack_running()
zts_stack_running = _libzt.zts_stack_running

def zts_ready():
    return _libzt.zts_ready()
zts_ready = _libzt.zts_ready

def zts_join(nwid):
    return _libzt.zts_join(nwid)
zts_join = _libzt.zts_join

def zts_leave(nwid):
    return _libzt.zts_leave(nwid)
zts_leave = _libzt.zts_leave

def zts_get_path(homePath, len):
    return _libzt.zts_get_path(homePath, len)
zts_get_path = _libzt.zts_get_path

def zts_get_node_id():
    return _libzt.zts_get_node_id()
zts_get_node_id = _libzt.zts_get_node_id

def zts_get_node_id_from_file(filepath):
    return _libzt.zts_get_node_id_from_file(filepath)
zts_get_node_id_from_file = _libzt.zts_get_node_id_from_file

def zts_has_address(nwid):
    return _libzt.zts_has_address(nwid)
zts_has_address = _libzt.zts_has_address

def zts_get_num_assigned_addresses(nwid):
    return _libzt.zts_get_num_assigned_addresses(nwid)
zts_get_num_assigned_addresses = _libzt.zts_get_num_assigned_addresses

def zts_get_address_at_index(nwid, index, addr):
    return _libzt.zts_get_address_at_index(nwid, index, addr)
zts_get_address_at_index = _libzt.zts_get_address_at_index

def zts_get_address(nwid, addr, address_family):
    return _libzt.zts_get_address(nwid, addr, address_family)
zts_get_address = _libzt.zts_get_address

def zts_get_6plane_addr(addr, nwid, nodeId):
    return _libzt.zts_get_6plane_addr(addr, nwid, nodeId)
zts_get_6plane_addr = _libzt.zts_get_6plane_addr

def zts_get_rfc4193_addr(addr, nwid, nodeId):
    return _libzt.zts_get_rfc4193_addr(addr, nwid, nodeId)
zts_get_rfc4193_addr = _libzt.zts_get_rfc4193_addr

def zts_get_peer_count():
    return _libzt.zts_get_peer_count()
zts_get_peer_count = _libzt.zts_get_peer_count

def zts_get_peer_address(peer, nodeId):
    return _libzt.zts_get_peer_address(peer, nodeId)
zts_get_peer_address = _libzt.zts_get_peer_address

def zts_allow_http_control(allowed):
    return _libzt.zts_allow_http_control(allowed)
zts_allow_http_control = _libzt.zts_allow_http_control

def zts_socket(socket_family, socket_type, protocol):
    return _libzt.zts_socket(socket_family, socket_type, protocol)
zts_socket = _libzt.zts_socket

def zts_connect(fd, addr, addrlen):
    return _libzt.zts_connect(fd, addr, addrlen)
zts_connect = _libzt.zts_connect

def zts_bind(fd, addr, addrlen):
    return _libzt.zts_bind(fd, addr, addrlen)
zts_bind = _libzt.zts_bind

def zts_listen(fd, backlog):
    return _libzt.zts_listen(fd, backlog)
zts_listen = _libzt.zts_listen

def zts_accept(fd, addr, addrlen):
    return _libzt.zts_accept(fd, addr, addrlen)
zts_accept = _libzt.zts_accept

def zts_setsockopt(fd, level, optname, optval, optlen):
    return _libzt.zts_setsockopt(fd, level, optname, optval, optlen)
zts_setsockopt = _libzt.zts_setsockopt

def zts_getsockopt(fd, level, optname, optval, optlen):
    return _libzt.zts_getsockopt(fd, level, optname, optval, optlen)
zts_getsockopt = _libzt.zts_getsockopt

def zts_getsockname(fd, addr, addrlen):
    return _libzt.zts_getsockname(fd, addr, addrlen)
zts_getsockname = _libzt.zts_getsockname

def zts_getpeername(fd, addr, addrlen):
    return _libzt.zts_getpeername(fd, addr, addrlen)
zts_getpeername = _libzt.zts_getpeername

def zts_gethostname(name, len):
    return _libzt.zts_gethostname(name, len)
zts_gethostname = _libzt.zts_gethostname

def zts_sethostname(name, len):
    return _libzt.zts_sethostname(name, len)
zts_sethostname = _libzt.zts_sethostname

def zts_gethostbyname(name):
    return _libzt.zts_gethostbyname(name)
zts_gethostbyname = _libzt.zts_gethostbyname

def zts_close(fd):
    return _libzt.zts_close(fd)
zts_close = _libzt.zts_close

def zts_select(nfds, readfds, writefds, exceptfds, timeout):
    return _libzt.zts_select(nfds, readfds, writefds, exceptfds, timeout)
zts_select = _libzt.zts_select

def zts_fcntl(fd, cmd, flags):
    return _libzt.zts_fcntl(fd, cmd, flags)
zts_fcntl = _libzt.zts_fcntl

def zts_ioctl(fd, request, argp):
    return _libzt.zts_ioctl(fd, request, argp)
zts_ioctl = _libzt.zts_ioctl

def zts_send(fd, buf, len, flags):
    return _libzt.zts_send(fd, buf, len, flags)
zts_send = _libzt.zts_send

def zts_sendto(fd, buf, len, flags, addr, addrlen):
    return _libzt.zts_sendto(fd, buf, len, flags, addr, addrlen)
zts_sendto = _libzt.zts_sendto

def zts_sendmsg(fd, msg, flags):
    return _libzt.zts_sendmsg(fd, msg, flags)
zts_sendmsg = _libzt.zts_sendmsg

def zts_recv(fd, buf, len, flags):
    return _libzt.zts_recv(fd, buf, len, flags)
zts_recv = _libzt.zts_recv

def zts_recvfrom(fd, buf, len, flags, addr, addrlen):
    return _libzt.zts_recvfrom(fd, buf, len, flags, addr, addrlen)
zts_recvfrom = _libzt.zts_recvfrom

def zts_recvmsg(fd, msg, flags):
    return _libzt.zts_recvmsg(fd, msg, flags)
zts_recvmsg = _libzt.zts_recvmsg

def zts_read(fd, buf, len):
    return _libzt.zts_read(fd, buf, len)
zts_read = _libzt.zts_read

def zts_write(fd, buf, len):
    return _libzt.zts_write(fd, buf, len)
zts_write = _libzt.zts_write

def zts_shutdown(fd, how):
    return _libzt.zts_shutdown(fd, how)
zts_shutdown = _libzt.zts_shutdown

def zts_add_dns_nameserver(addr):
    return _libzt.zts_add_dns_nameserver(addr)
zts_add_dns_nameserver = _libzt.zts_add_dns_nameserver

def zts_del_dns_nameserver(addr):
    return _libzt.zts_del_dns_nameserver(addr)
zts_del_dns_nameserver = _libzt.zts_del_dns_nameserver
# This file is compatible with both classic and new-style classes.


