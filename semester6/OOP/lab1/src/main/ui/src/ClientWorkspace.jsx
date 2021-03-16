import { Component } from "react";
import Greeting from "./Greeting.jsx";
import $ from "jquery"

class DeveloperWorkspace extends Component {

    async postData(url = '', data = {}) {
        const response = await fetch(url,
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify(data)
            });
        return await response.json();
    }

    componentDidMount() {
        this.postData('http://localhost:8080/lab1/client', {
            action: 'listbooks'
        })
            .then((data) => {
                let select = $('#books');
                $.each(data, function (index, item) {
                    select.append('<option name="projects" value="' + item.id + '">' + item.name + '</option>');
                });
                let ans = $('#answer');
                ans.attr("bgcolor","pink");
            });

        $(document).on("clicl", "#take_book", function (event) {
            this.postData('http://localhost:8080/lab1/client', {
                action: 'takebook'
            })
                .then((data) => {
                    let ans = $('#answer');
                    if (data.id != "-1") {
                        ans.attr("bgcolor","red");
                    } else {
                        ans.attr("bgcolor","green");
                    }
                })
        })

    }
    render() {
        return (
            <div>
                <Greeting />
                <br />
                Developer
                <table>
                    <tbody>
                        <tr>
                            <td>Books</td>
                            <td bgcolor="green">
                                <select id="books" size="3" width="100%"></select>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <button id="take_book">Take book</button>
                            </td>
                            <td id="answer" width="10px" height="10px">
                                {/* <div id="answer"></div> */}
                            </td>
                        </tr>
                    </tbody>
                </table>
            </div>
        )
    }
}

export default DeveloperWorkspace;