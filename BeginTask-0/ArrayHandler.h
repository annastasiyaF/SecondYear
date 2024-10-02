
template<typename T>
class ArrayHandler {
private:
    int8_t _max;
    int8_t _min;
    int8_t _size;
    size_t _max_size;
    T* _array;
    T* _id_array;
    size_t _count;

public:
    ArrayHandler(int size = 10){
        _size = size;
        _id_array = new int8_t[_max_size];
        _max = INT32_MIN;
        _min = INT32_MAX;
        _count = 0;
        for (int i = 0; i < 10 ;i++){
            _id_array[i] = -1;
        }
    }

    void Append(int8_t new_element){
        if (new_element > _max){
            _max = new_element;
        }
        if (new_element < _min){
            _min = new_element;
        }
        if (_count == _max_size) {
            _max_size += 10;
            int8_t* new_arr = new int8_t[_max_size];
            std::memcpy(new_arr, _array, _count*sizeof(int8_t));
            delete [] _array;
            _array = new_arr;
        }
        _array[_count] = new_element;
        _count++;
    }

    bool IsContains(T elem) {
        return false;
    }

    T GetMax() {
        for (int i = 0; i < _count; i++) {
            if (_max < _array[i])
                _max = _array[i];
        }
        return _max;
    }

    T GetMin() {
        for (int i = 0; i < _count; i++) {
            if (_min > _array[i])
                _min = _array[i];
        }
        return _min;
    }

    ~ArrayHandler() {
        delete [] _array;
    }

};