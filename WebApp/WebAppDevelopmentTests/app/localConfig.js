

exports.config = {
    dbConfig: {
        host: "localhost",
        user: "root",
        password: "",
        database: "meteostationdb",

        pooledConnections: 125,
        idleTimeoutMillis: 30000
    },

    staticContent: "../public/"
};

