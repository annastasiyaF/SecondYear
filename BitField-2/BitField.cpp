#include "BitField.h"


size_t BitField::GetMemIndex(size_t n) const{
    if (n >= _sizeBit)
        throw "Bit out of range!";
    size_t index = n / (8 * sizeof(uint16_t));
}
uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n % (8 * sizeof(uint16_t)));
}

BitField::BitField(size_t len) {
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
}

BitField& BitField::operator=(const BitField& tmp) {
    if (_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    for (size_t i = 0; i < _memSize; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}
    
size_t BitField::GetLength() const {
    return _sizeBit;
}
void BitField::SetBit(size_t n) {
    _mem[GetMemIndex(n)] |= GetMask(n);
}
void BitField::ClrBit(size_t n) {
    uint16_t mask = GetMask(n);
    mask =~ mask;
    _mem[GetMemIndex(n)] &= mask;
}
uint8_t BitField::GetBit(size_t n) const {
    return (_mem[GetMemIndex(n)] & GetMask(n)) != 0;
}
BitField BitField::operator|(const BitField& tmp) {
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] = _mem[i] | tmp._mem[i];
    }
    return B;
}

BitField BitField::operator&(const BitField& tmp) {
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] = _mem[i] & tmp._mem[i];
    }
    return B;
}
BitField BitField::operator^(const BitField& tmp) {
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] = _mem[i] ^ tmp._mem[i];
    }
    return B;
}
bool BitField::operator==(const BitField& tmp) const{
    for (size_t i=0; i<_memSize; i++){
        if (_mem[i] != tmp._mem[i]){
            return false;
        }
    }
    return true;
}
BitField BitField::operator~(){
    BitField cpy = BitField(*this);
    for (size_t i=0; i<_sizeBit; i++){
        if (GetBit(i)){
            cpy.ClrBit(i);
        }
        else{
            cpy.SetBit(i);
        }
    }
    return cpy;
}