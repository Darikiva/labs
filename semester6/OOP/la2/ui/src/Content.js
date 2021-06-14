import {BrowserRouter, Route} from "react-router-dom";
import Login from "./Login";
import React, {useState, useEffect} from 'react';
import NavBar from "./NavBar";
import Librarian from "./LibrarianWorkspace";
import Client from "./ClientWorkspace";

function Content() {
    const qs = require("qs")
    const [user, setUser] = useState(qs.parse(sessionStorage.getItem('user')));
    const initialUser = {
        username: '',
        password: '',
        lastName: '',
        firstName: ''
    };
    const [loggedIn, setLoggedIn] = useState(false)

    useEffect(() => {
            if (user) {
                if (user.token) {
                    if (user.token !== '') {
                        setLoggedIn(true)
                    }
                }
            }
        }, [user]
    )

    const logOut = () => {
        setUser(initialUser)
        setLoggedIn(false)
        sessionStorage.removeItem('user')
    }

    return (
        <div>
            <BrowserRouter>
                <NavBar user={user} loggedIn={loggedIn} logOut={logOut}/>
                <div className={"container"}>
                    <Route exact path="/login">
                        <Login initialUser={initialUser} setUser={setUser} setLoggedIn={setLoggedIn}
                               loggedIn={loggedIn}/>
                    </Route>
                    <Route exact path={"/"}>
                        {(user.role === "user") &&
                        <div>
                            <Client token={user.token} loggedIn={loggedIn}/>
                        </div>
                        }
                        {(user.role === "admin") &&
                        <div>
                            <Librarian token={user.token} loggedIn={loggedIn}/>
                        </div>
                        }
                    </Route>
                </div>
            </BrowserRouter>
        </div>
    );
}

export default Content;