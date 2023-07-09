const mongoose = require('mongoose');

const Time = mongoose.Schema({
    Heating : {
        require: true,
        type: Number,
    },
    Light_Level: {
        require: true,
        type: Number,
    },
    Activation : {
        require: true,
        type: Number,
    },
    Pause : {
        require: true,
        type: Number,
    },
});

module.exports = mongoose.model('Times', Time);