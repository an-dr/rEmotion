# Src: 


import framebuf

'''
When starting a transmission a start byte is required. It consists of 5 consecutive 〝1〞（sync character）. Serial transfer counter
will be reset and synchronized. Following 2 bits for read(1)/write(0)（RW）and register(0)/data(1) select（RS）. Last 4 bits is filled by 〝0〞。

After receiving the sync character and RW and RS bits, every 8 bits instruction/data will be separated into 2 groups. Higher
4 bits（DB7~DB4）will be placed in first section followed by 4 〝0〞. And lower 4 bits（DB3~DB0）will be placed in second
section followed by 4 〝0
'''

class LCD12864(framebuf.FrameBuffer):
    SYNC = 0b11111000
    
    def __init__(self, spi, cs):
        self._spi = spi
        self._cs = cs
        self.width = 128
        self.height = 64
        self._buf = bytearray(128 * 64 // 2)
        self._bufmv = memoryview(self._buf)
        super().__init__(self._buf, 128, 64, framebuf.MONO_HLSB)
        self._disp_init()
    
    def _disp_init(self):
        self.write_cmd(0x30)
        self.write_cmd(0x30)
        self.write_cmd(0xC)
        self.write_cmd(0x34)
        self.write_cmd(0x34)
        self.write_cmd(0x36)
        
    def _send(self, buf):
        self._cs(1)
        self._spi.write(buf)
        self._cs(0)

    def _format_byte(self, byte):
        return [byte & 0xf0, (byte & 0xf) << 4]

    def write_cmd(self, cmd):
        buf = [self.SYNC]
        if isinstance(cmd, int):
            buf += self._format_byte(cmd)
        else:
            for c in cmd:
                buf += self._format_byte(c)
        self._send(bytes(buf))
        
    def write_data(self, data: bytearray):
        buf = [self.SYNC | 0x2]
        for b in data:
            buf += self._format_byte(b)
        self._send(bytes(buf))

    def set_address(self, x, y):
        self.write_cmd([0x80 + y, 0x80 + x])
        
    def show(self):
        for j in range(2):
            for i in range(32):
                self.set_address(8*j, i)
                self.write_data(self._bufmv[(512 * j) + i * 16 : (512 * j) + (16 + i * 16)])
