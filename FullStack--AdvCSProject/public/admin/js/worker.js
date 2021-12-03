var navbar = document.getElementById("navbar");
navbar.innerHTML += createNav("admin");

/* eslint-disable quotes */
fetch("/api/users/workers")
	.then((response) => {
		return response.json();
	})
	.then((data) => {
		console.log(data);
		var list = document.getElementById("workerList");

		for (let i = 0; i < data.length; i++) {
			list.innerHTML +=
				' <div class="card">' +
				`<div class="card-header" id ="${data[i].id}">` +
				' <h2 class="mb-0">' +
				` <button class="btn btn-link collapsed" type="button" data-toggle="collapse" data-target="#collapse${data[i].id}" aria-expanded="false" aria-controls="collapse${data[i].id}">` +
				`Email: ${data[i].email} 	job: ${data[i].groupname}` +
				` </button>` +
				`</h2>` +
				`</div>` +
				`<div id="collapse${data[i].id}" class="collapse" aria-labelledby = "${data[i].id}" data-parent="#workerList">` +
				`<div class="card-body">` +
				`<ul>Name: ${isFilled(data[i].firstName, data[i].familyName)}  ID: ${
					data[i].id
				}	</ul><ul>` +
				`</div>` +
				`</div>` +
				`</div>`;
		}
		list.innerHTML += "<br><br>";
	})
	.catch((err) => {
		console.log(err);
		// Do something for an error here
	});

function isFilled(name, lastname) {
	console.log(name, lastname);
	if (name !== null && lastname !== null) {
		return name + " " + lastname;
	} else if (name === null && lastname != null) {
		return lastname;
	} else if (name != null && lastname === null) {
		return name;
	}
	return "Not given";
}
