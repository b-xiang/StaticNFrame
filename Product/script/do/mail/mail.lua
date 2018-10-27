module("mailsys", package.seeall)

--[[
mail = {
	id = 0,
	mailType = 0,
	read = false,
	time = 0,
	subject = "",
	content = "",
	attachments = {},
}
--]]
MAIL_DB = "mail"

function create(id, mailType, subject, content, attachments)
	local mail = {
		id = id,
		mailType = mailType,
		read = false,
		time = os.time()
	}

	if subject ~= nil and type(subject) == 'string' then
		mail.subject = subject
	end

	if content ~= nil and type(content) == 'string' then
		mail.text = text
	end

	return mail
end

function sendCustom(uid, subject, content, attachments)
	local userInfo = GetUserInfoById(uid)

	if userInfo == nil then
		local mail = create(0, 1, subject, content, attachments)
		save(uid, mail)
	else
		userInfo.mailMgr:addNew(1, subject, content)
	end
end

function sendStandard(uid, mailType, attachments)
	local userInfo = UserInfo.GetUserInfoById(uid)

	if userInfo == nil then
		local mail = create(0, mailType)
		save(uid, mail)
	else
		userInfo.mailMgr:addNew(mailType)
	end
end

function save(uid, mail)
	local data = unilight.getdata("mail", uid)
	
	if data == nil then 
		unilight.debug("Can not get mail about uid:" .. uid)

		data = {
			uid = uid,
			id = 0,
			mails = {}
		}
	end

	if data.mails == nil then
		unilight.debug("mail is nil, UID:" .. uid)
		data.mails = {}
	end

	if #data.mails == MAIL_MAX then
		table.remove(data.mails, 1)
	end

	data.id = data.id + 1
	mail.id = data.id
	table.insert(data.mails, mail)

	unilight.savedata(MAIL_DB, data)
end
