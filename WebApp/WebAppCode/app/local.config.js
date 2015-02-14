

exports.config = {
    dbConfig: {
        host: "localhost",
        user: "root",
        password: "",
        database: "meteostationd",

        pooledConnections: 125,
        idleTimeoutMillis: 30000
    },

    static_content: "../static/"
};

